const events = require("events");
const os = require("os");
const natives = require("../build/Release/native_metrics.node");

type gcTypes =
  | "Scavenge"
  | "MinorMarkCompact"
  | "MarkSweepCompact"
  | "IncrementalMarking"
  | "ProcessWeakCallbacks"
  | "All";
class NativeMetricEmitter extends events.EventEmitter {
  private static GC_TYPES: { [key: number]: gcTypes } = {
    1: "Scavenge",
    2: "MarkSweepCompact",
    3: "All", // For <= node4

    4: "IncrementalMarking",
    8: "ProcessWeakCallbacks",

    15: "All" // For > node4
  };

  // Node 18 and newer
  // https://v8docs.nodesource.com/node-18.2/db/d88/v8-callbacks_8h_source.html
  private static GC_TYPES_NEW: { [key: number]: gcTypes } = {
    1: "Scavenge",
    2: "MinorMarkCompact",
    4: "MarkSweepCompact",
    8: "IncrementalMarking",
    16: "ProcessWeakCallbacks",
    31: "All"
  };

  private static DEFAULT_INTERVAL = 15000;

  private enabled: boolean;
  private _handle: any;
  private _loopProfiler: any;
  private _gcProfiler: any;
  private _resourceProfiler: any;
  private _nodeMajVer: number;

  constructor(options: any) {
    super(options);

    this._nodeMajVer = parseInt(process.versions.node.split('.')[0], 10);

    options = options || { timeout: NativeMetricEmitter.DEFAULT_INTERVAL };
    this.enabled = false;
    this._handle = null;

    this._loopProfiler = new natives.LoopProfiler();
    this._gcProfiler = new natives.GcProfiler();
    this._resourceProfiler = new natives.ResourceProfiler();

    this.enable(true, options.timeout);
  }

  public enable(enable: boolean = true, pollInterval?: number) {
    if (enable) {
      this._start(pollInterval);
    } else {
      this._stop();
    }
  }

  public getLoopData() {
    return this._loopProfiler.data();
  }

  public getGCData() {
    const gcMetrics: any[] = this._gcProfiler.data();
    const results = Object.create(null);
    for (let typeId in gcMetrics) {
      if (gcMetrics.hasOwnProperty(typeId) && gcMetrics[typeId].count > 0) {
        let typeName = "";
        if (this._nodeMajVer >= 18) {
          typeName = NativeMetricEmitter.GC_TYPES_NEW[typeId];
        }
        else {
          typeName = NativeMetricEmitter.GC_TYPES[typeId];
        }
        results[typeName] = {
          typeId: parseInt(typeId, 10),
          type: typeName,
          metrics: gcMetrics[typeId]
        };
      }
    }

    return results;
  }

  private _start(pollInterval?: number) {
    if (this.enabled) {
      return;
    }

    const interval = pollInterval || NativeMetricEmitter.DEFAULT_INTERVAL;

    this._gcProfiler.start();
    this._loopProfiler.start();

    this._handle = setTimeout(this._emitUsage.bind(this, interval), interval);
    this._handle.unref();

    this.enabled = true;
  }

  private _stop() {
    if (!this.enabled) {
      return;
    }

    this._gcProfiler.stop();
    this._loopProfiler.stop();

    clearTimeout(this._handle);
    this._handle = null;

    this.enabled = false;
  }

  private _emitUsage(interval: number) {
    if (this._resourceProfiler) {
      this.emit("usage", this._resourceProfiler.read());
    }
    if (this.enabled) {
      // Stop timer when disabled
      this._handle = setTimeout(this._emitUsage.bind(this, interval), interval);
      this._handle.unref();
    }
  }
}

export = NativeMetricEmitter;

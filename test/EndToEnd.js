"use strict";

const assert = require("assert");
var NativeMetricEmitter = require("../out/main");
const emitter = new NativeMetricEmitter();

describe("#EndToEnd", () => {
  it("should collect manual global.gc events", () => {
    if (emitter._gcProfiler) {
      emitter.getGCData(); // clear any transient GCs

      // Verify precondition
      assert.deepEqual({}, emitter.getGCData());

      // Act
      global.gc(); // should trigger MarkSweepCompact

      // Test postcondition
      const gcMetrics = emitter.getGCData();
      const gcTypes = Object.keys(gcMetrics);

      assert.notDeepEqual({}, gcMetrics);
      assert.equal(gcTypes.length, 1);
      assert.equal(gcTypes[0], NativeMetricEmitter.GC_TYPES[2]);

      assert.deepEqual({}, emitter.getGCData());
    } else {
      assert.ok(false, "gc not enabled");
    }
  });

  it("should send resource usage information", done => {
    emitter.enable(false);
    emitter.enable(true, 100);
    if (emitter._resourceProfiler) {
      emitter.on("usage", usage => {
        assert.ok(usage);
        emitter.enable(false);
        emitter.enable();
        done();
      });
    } else {
      assert.ok(false);
      emitter.enable(false);
      emitter.enable();
      done();
    }
  });

  it("should send event loop information", () => {
    if (emitter._loopProfiler) {
      assert.ok(emitter.getLoopData());
    } else {
      assert.ok(false);
    }
  });
});

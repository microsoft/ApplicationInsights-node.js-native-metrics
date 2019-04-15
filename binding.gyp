{
	"targets": [
		{
			"target_name": "native_metrics",
			"sources": [
				"src/GcProfiler.cc",
				"src/LoopProfiler.cc",
				"src/LoopProfiler.hh",
				"src/Metric.hh",
				"src/ResourceProfiler.cc",
				"src/ResourceProfiler.hh",
				"src/native_metrics.cc"
			 ],
			"defines": [
				"NOMINMAX"
			],
			"include_dirs": [
				"src",
        		"<!(node -e \"require('nan')\")"
      		]
		}
	]
}

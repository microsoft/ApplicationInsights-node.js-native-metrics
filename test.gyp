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
  		}, {
			"target_name": "test_native",
			"sources": [
				"external/googletest/googletest/include/gtest/gtest.h",
				"external/googletest/googletest/src/gtest-all.cc",

				"test_native/main.cc",
				"test_native/metrics_tests.cc"
			],
			"defines": [
				"NOMINMAX"
			],
			"include_dirs": [
				"external/googletest/googletest",
				"external/googletest/googletest/include",
				"src",
				"test_native",
				"<!(node -e \"require('nan')\")"
			]
		}
	]
}

#include "snow.h"

describe(dummy_suitcase, {
	subdesc(dummy _testcase, {
		it("dummy", {
			asserteq_int(1, 1);
		});
	});
});


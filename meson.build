project('isokat', 'c',
	version: '0.1.3',
	default_options: [
		'c_std=c11',
		'werror=true',
	])

default_args = ['-D_POSIX_C_SOURCE=200112L', '-D_XOPEN_SOURCE=500', '-Wwrite-strings']
dep_criterion = dependency('criterion')

src = [
  'src/formats/common.c',
  'src/cJSON.c',
  'src/http.c',
  'src/http_parser.c',
  'src/zf_log.c',
]

incdir = include_directories('include')

executable('isokat',
	src, 'src/main.c',
	include_directories : incdir,
	c_args: default_args)

src_tests = [
	'tests/formats/test_common.c',
	'tests/test_http.c',
]

foreach filename : src_tests
    t = filename.split('.c')[0].split('/')

    test_args = '--color=always'
    
    test(t[-1], executable(t[-1], filename,
				src,
				dependencies: dep_criterion,
				include_directories : incdir,
				c_args: default_args))
endforeach
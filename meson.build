project('isokat', 'c',
	version: '0.1.3',
	default_options: [
		'c_std=c11',
		'werror=true',
	])

cc = meson.get_compiler('c')

default_args = ['-D_POSIX_C_SOURCE=200112L', '-D_XOPEN_SOURCE=500', '-Wwrite-strings']
dep_criterion = dependency('criterion')
dep_libxml = dependency('libxml-2.0', required: true)
dep_libconfig = dependency('libconfig', version: '>=1.7', required: true)

src = [
  'src/formats/common.c',
  'src/formats/xml.c',
  'src/cJSON.c',
  'src/context.c',
  'src/http.c',
  'src/zf_log.c',
  'src/http_parser.c',
]

incdir = include_directories('include')

executable('isokat',
	src, 
	'src/main.c',
	include_directories : incdir,
	dependencies: [dep_libxml, dep_libconfig],
	c_args: default_args)

src_tests = [
	'tests/formats/test_common.c',
	'tests/formats/test_xml.c',
	'tests/test_context.c',
	'tests/test_http.c',
]

foreach filename : src_tests
    t = filename.split('.c')[0].split('/')

    test_args = '--color=always'
    
    test(t[-1], executable(t[-1], filename,
				src,
				dependencies: [dep_criterion, dep_libxml],
				include_directories : incdir,
				c_args: default_args))
endforeach
project('isokat', 'c',
	version: '0.1.4',
	default_options: [
		'c_std=c11',
		'werror=true',
	])

cc = meson.get_compiler('c')

cdata = configuration_data()
cdata.set_quoted('VERSION', meson.project_version())
cdata.set_quoted('TOPDIR', meson.current_source_dir())
config_h = configure_file(output: 'config.h', configuration: cdata)

default_args = ['-D_POSIX_C_SOURCE=200112L', '-D_XOPEN_SOURCE=500', '-Wwrite-strings', '-DHAVE_CONFIG_H']
dep_criterion = dependency('criterion')
dep_libxml = dependency('libxml-2.0', required: true)
dep_libconfig = dependency('libconfig', version: '>=1.7', required: true)

app_gengetopt = find_program('gengetopt', required: true)

src_cmdline = custom_target('ggo',
            input: ['isokat.ggo'],
            output: ['cmdline.h', 'cmdline.c'],
            depend_files: [config_h],
            command: [app_gengetopt.path(),
                      '--show-required', '--input=@INPUT@'])

src = [
  'src/formats/common.c',
  'src/formats/xml.c',
  'src/cJSON.c',
  'src/conf.c',
  'src/context.c',
  'src/http.c',
  'src/zf_log.c',
  'src/http_parser.c',
]

incdir = include_directories('include')

executable('isokat',
	src, 
	src_cmdline,
	'src/main.c',
	include_directories : incdir,
	dependencies: [dep_libxml, dep_libconfig],
	c_args: default_args)

src_tests = [
	'tests/formats/test_common.c',
	'tests/formats/test_xml.c',
	'tests/test_conf.c',
	'tests/test_context.c',
	'tests/test_http.c',
]

foreach filename : src_tests
    t = filename.split('.c')[0].split('/')

    test_args = '--color=always'
    
    test(t[-1], executable(t[-1], filename,
				src,
				src_cmdline,
				dependencies: [dep_criterion, dep_libxml, dep_libconfig],
				include_directories : incdir,
				c_args: default_args))
endforeach
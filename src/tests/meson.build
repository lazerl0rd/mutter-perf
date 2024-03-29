mutter_test_sources = [
  'meta-backend-test.c',
  'meta-backend-test.h',
  'meta-context-test.c',
  'meta-gpu-test.c',
  'meta-gpu-test.h',
  'meta-monitor-manager-test.c',
  'meta-monitor-manager-test.h',
  'meta-sensors-proxy-mock.c',
  'meta-sensors-proxy-mock.h',
  'monitor-test-utils.c',
  'monitor-test-utils.h',
  'meta-test-utils.c',
  'meta-test-utils.h',
]

libmutter_test_name = 'mutter-test-' + libmutter_api_version

clutter_test_utils = files (
  'clutter-test-utils.c',
  'clutter-test-utils.h',
)

tests_includepath = include_directories('.')
tests_includes = mutter_includes
tests_c_args = mutter_c_args

tests_deps = [
  mutter_deps,
  libmutter_dep,
  libmutter_cogl_dep,
  libmutter_clutter_dep,
]

libmutter_test = shared_library(libmutter_test_name,
                                mutter_test_sources,
                                gnu_symbol_visibility: 'hidden',
                                include_directories: tests_includes,
                                c_args: tests_c_args,
                                dependencies: tests_deps,
                                install_rpath: pkglibdir,
                                install_dir: libdir,
                                install: true,
)

libmutter_test_dep = declare_dependency(
  link_with: libmutter_test,
  include_directories: tests_includes,
  dependencies: tests_deps,
)

pkg.generate(libmutter_test,
  name: 'Meta (test framework)',
  filebase: 'libmutter-test-' + libmutter_api_version,
  description: 'Mutter test framework',
  subdirs: pkgname,
  requires: ['libmutter-' + libmutter_api_version],
  version: meson.project_version(),
  variables: [
    'apiversion=' + libmutter_api_version,
  ],
  install_dir: pcdir,
)

if have_clutter_tests
  subdir('clutter')
endif

subdir('meta-test')
subdir('wayland-test-clients')

if have_installed_tests
  stacking_files_datadir = join_paths(pkgdatadir, 'tests')

  installed_tests_cdata = configuration_data()
  installed_tests_cdata.set('libexecdir', libexecdir)
  installed_tests_cdata.set('apiversion', libmutter_api_version)

  configure_file(
    input: 'mutter-all.test.in',
    output: 'mutter-all.test',
    configuration: installed_tests_cdata,
    install: true,
    install_dir: mutter_installed_tests_datadir,
  )

  install_subdir('stacking', install_dir: stacking_files_datadir)
endif

test_env = environment()
test_env.set('G_TEST_SRCDIR', join_paths(mutter_srcdir, 'src'))
test_env.set('G_TEST_BUILDDIR', mutter_builddir)
test_env.set('MUTTER_TEST_PLUGIN_PATH', '@0@'.format(default_plugin.full_path()))

test_client = executable('mutter-test-client',
  sources: ['test-client.c'],
  include_directories: tests_includes,
  c_args: tests_c_args,
  dependencies: [
    gtk3_dep,
    gio_unix_dep,
    x11_dep,
    xext_dep,
  ],
  install: have_installed_tests,
  install_dir: mutter_installed_tests_libexecdir,
)

test_runner = executable('mutter-test-runner',
  sources: [
    'test-runner.c',
  ],
  include_directories: tests_includes,
  c_args: tests_c_args,
  dependencies: libmutter_test_dep,
  install: have_installed_tests,
  install_dir: mutter_installed_tests_libexecdir,
)

if have_installed_tests
  install_data('meta-dbus-runner.py',
    install_dir: mutter_installed_tests_libexecdir,
  )
  install_subdir('dbusmock-templates',
    install_dir: mutter_installed_tests_libexecdir,
  )
endif

unit_tests = executable('mutter-test-unit-tests',
  sources: [
    'unit-tests.c',
    'boxes-tests.c',
    'boxes-tests.h',
    'meta-gpu-test.c',
    'meta-gpu-test.h',
    'monitor-config-migration-unit-tests.c',
    'monitor-config-migration-unit-tests.h',
    'monitor-store-unit-tests.c',
    'monitor-store-unit-tests.h',
    'monitor-test-utils.c',
    'monitor-test-utils.h',
    'monitor-transform-tests.c',
    'monitor-transform-tests.h',
    'monitor-unit-tests.c',
    'orientation-manager-unit-tests.c',
    'monitor-unit-tests.h',
  ],
  include_directories: tests_includes,
  c_args: tests_c_args,
  dependencies: libmutter_test_dep,
  install: have_installed_tests,
  install_dir: mutter_installed_tests_libexecdir,
)

headless_start_test = executable('mutter-headless-start-test',
  sources: [
    'headless-start-test.c',
  ],
  include_directories: tests_includes,
  c_args: tests_c_args,
  dependencies: libmutter_test_dep,
  install: have_installed_tests,
  install_dir: mutter_installed_tests_libexecdir,
)

stage_view_tests = executable('mutter-stage-view-tests',
  sources: [
    'monitor-test-utils.c',
    'monitor-test-utils.h',
    'stage-view-tests.c',
  ],
  include_directories: tests_includes,
  c_args: tests_c_args,
  dependencies: libmutter_test_dep,
  install: have_installed_tests,
  install_dir: mutter_installed_tests_libexecdir,
)

wayland_tests = executable('mutter-wayland-tests',
  sources: [
    'meta-wayland-test-driver.c',
    'meta-wayland-test-driver.h',
    'wayland-unit-tests.c',
    test_driver_server_header,
    test_driver_protocol_code,
  ],
  include_directories: tests_includes,
  c_args: tests_c_args,
  dependencies: libmutter_test_dep,
  install: have_installed_tests,
  install_dir: mutter_installed_tests_libexecdir,
)

anonymous_file_test = executable('anonymous-file-tests',
  sources: [
    'anonymous-file.c',
  ],
  include_directories: tests_includes,
  c_args: tests_c_args,
  dependencies: [tests_deps],
  install: have_installed_tests,
  install_dir: mutter_installed_tests_libexecdir,
)

ref_test_sources = [
  'meta-ref-test.c',
  'meta-ref-test.h',
]

if have_native_tests
  native_kms_utils_tests = executable('mutter-native-kms-utils-tests',
    sources: [
      'kms-utils-unit-tests.c',
    ],
    include_directories: tests_includepath,
    c_args: tests_c_args,
    dependencies: [tests_deps],
    install: have_installed_tests,
    install_dir: mutter_installed_tests_libexecdir,
  )

  native_headless_tests = executable('mutter-native-headless-tests',
    sources: [
      'native-headless.c',
      'native-screen-cast.c',
      'native-screen-cast.h',
      'native-virtual-monitor.c',
      'native-virtual-monitor.h',
      ref_test_sources,
    ],
    include_directories: tests_includes,
    c_args: tests_c_args,
    dependencies: libmutter_test_dep,
    install: have_installed_tests,
    install_dir: mutter_installed_tests_libexecdir,
  )

  ref_test_sanity = executable('mutter-ref-test-sanity',
    sources: [
      'ref-test-sanity.c',
      ref_test_sources,
    ],
    include_directories: tests_includes,
    c_args: tests_c_args,
    dependencies: libmutter_test_dep,
    install: have_installed_tests,
    install_dir: mutter_installed_tests_libexecdir,
  )

  screen_cast_client = executable('mutter-screen-cast-client',
    sources: [
      'screen-cast-client.c',
      dbus_screen_cast_built_sources,
    ],
    include_directories: tests_includes,
    c_args: tests_c_args,
    dependencies: [
      gio_dep,
      libpipewire_dep,
    ],
    install: have_installed_tests,
    install_dir: mutter_installed_tests_libexecdir,
  )

  native_persistent_virtual_monitor = executable(
    'mutter-persistent-virtual-monitor',
    sources: [
      'native-persistent-virtual-monitor.c',
    ],
    include_directories: tests_includes,
    c_args: tests_c_args,
    dependencies: libmutter_test_dep,
    install: have_installed_tests,
    install_dir: mutter_installed_tests_libexecdir,
  )
endif

stacking_tests = [
  'basic-x11',
  'basic-wayland',
  'client-side-decorated',
  'closed-transient',
  'closed-transient-no-default-focus',
  'closed-transient-no-input-no-take-focus-parent',
  'closed-transient-no-input-no-take-focus-parents',
  'closed-transient-no-input-parent',
  'closed-transient-no-input-parent-delayed-focus-default-cancelled',
  'closed-transient-no-input-parents',
  'closed-transient-no-input-parents-queued-default-focus-destroyed',
  'closed-transient-only-take-focus-parents',
  'minimized',
  'mixed-windows',
  'set-parent',
  'override-redirect',
  'set-override-redirect-parent',
  'set-parent-exported',
  'restore-size',
  'unmaximize-new-size',
  'fullscreen-maximize',
  'restore-position',
  'default-size',
  'modals',
  'map-fixed-size',
]

foreach stacking_test: stacking_tests
  test(stacking_test, test_runner,
    suite: ['core', 'mutter/stacking'],
    env: test_env,
    args: [
      files(join_paths('stacking', stacking_test + '.metatest')),
    ],
    is_parallel: false,
    timeout: 60,
  )
endforeach

test('normal', unit_tests,
  suite: ['core', 'mutter/unit'],
  env: test_env,
  is_parallel: false,
  timeout: 60,
)

test('headless-start', headless_start_test,
  suite: ['core', 'mutter/unit'],
  env: test_env,
  is_parallel: false,
  timeout: 60,
)

test('stage-view', stage_view_tests,
  suite: ['core', 'mutter/unit'],
  env: test_env,
  is_parallel: false,
  timeout: 60,
)

test('wayland', wayland_tests,
  suite: ['core', 'mutter/unit'],
  env: test_env,
  is_parallel: false,
  timeout: 60,
)

test('anonymous-file', anonymous_file_test,
  suite: ['core', 'mutter/unit'],
  env: test_env,
  is_parallel: false,
  timeout: 60,
)

if have_native_tests
  test('native-kms-utils', native_kms_utils_tests,
    suite: ['core', 'mutter/native/kms'],
    env: test_env,
    is_parallel: false,
    timeout: 60,
  )

  test('native-headless', native_headless_tests,
    suite: ['core', 'mutter/native/headless'],
    env: test_env,
    is_parallel: false,
    timeout: 60,
  )

  test('ref-test-sanity', ref_test_sanity,
    suite: ['core', 'mutter/ref-test/sanity'],
    env: test_env,
    is_parallel: false,
    timeout: 60,
  )

  test('native-persistent-virtual-monitor', native_persistent_virtual_monitor,
    suite: ['core', 'mutter/native/persistent-virtual-monitor'],
    env: test_env,
    is_parallel: false,
    timeout: 60,
  )
endif

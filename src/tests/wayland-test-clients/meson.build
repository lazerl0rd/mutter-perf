wayland_test_client_installed_tests_libexecdir = join_paths(
  mutter_installed_tests_libexecdir,
  'wayland-test-clients',
)

test_driver_server_header = custom_target(
  'test-driver server header',
  input: 'test-driver.xml',
  output: 'test-driver-server-protocol.h',
  command: [
    wayland_scanner,
    'server-header',
    '@INPUT@', '@OUTPUT@',
  ]
)

test_driver_client_header = custom_target(
  'test-driver client header',
  input: 'test-driver.xml',
  output: 'test-driver-client-protocol.h',
  command: [
    wayland_scanner,
    'client-header',
    '@INPUT@', '@OUTPUT@',
  ]
)

test_driver_protocol_code = custom_target(
  'test-driver source',
  input: 'test-driver.xml',
  output: 'test-driver-protocol.c',
  command: [
    wayland_scanner,
    'private-code',
    '@INPUT@', '@OUTPUT@',
  ]
)

common_sources = [
  'wayland-test-client-utils.c',
  'wayland-test-client-utils.h',
  wayland_protocol_client_headers,
  wayland_protocol_sources,
  test_driver_client_header,
  test_driver_protocol_code,
]

wayland_test_clients = [
  'subsurface-remap-toplevel',
  'subsurface-reparenting',
  'invalid-subsurfaces',
  'invalid-xdg-shell-actions',
  'xdg-apply-limits',
  'xdg-activation',
]

foreach test : wayland_test_clients
  executable(test,
    sources: [
      '@0@.c'.format(test),
      common_sources,
    ],
    include_directories: tests_includes,
    c_args: tests_c_args,
    dependencies: [
      glib_dep,
      wayland_client_dep,
    ],
    install: have_installed_tests,
    install_dir: wayland_test_client_installed_tests_libexecdir,
  )
endforeach

msgfmt = find_program('msgfmt')

custom_target('mutter.desktop',
  input: 'mutter.desktop.in',
  output: 'mutter.desktop',
  command: [
    msgfmt,
    '--desktop', '--template',
    '@INPUT@',
    '-d', join_paths(mutter_srcdir, 'po'),
    '-o', '@OUTPUT@'
  ],
  install: true,
  install_dir: join_paths(datadir, 'applications'),
)

# Unconditionally use this dir to avoid a circular dep with gnomecc
gnome_keybindings_keysdir = join_paths(datadir, 'gnome-control-center/keybindings')

keybinding_xml_files = [
  '50-mutter-navigation.xml',
  '50-mutter-system.xml',
  '50-mutter-windows.xml',
]

if have_wayland
  keybinding_xml_files += [
    '50-mutter-wayland.xml',
  ]
endif

install_data(keybinding_xml_files,
  install_dir: gnome_keybindings_keysdir,
)

xwayland_grab_default_access_rules = get_option('xwayland_grab_default_access_rules')

gschema_config = configuration_data()
gschema_config.set('GETTEXT_DOMAIN', meson.project_name())
gschema_config.set('XWAYLAND_GRAB_DEFAULT_ACCESS_RULES',
                   xwayland_grab_default_access_rules)

schemadir = join_paths(datadir, 'glib-2.0', 'schemas')
configure_file(
  input: 'org.gnome.mutter.gschema.xml.in',
  output: 'org.gnome.mutter.gschema.xml',
  configuration: gschema_config,
  install_dir: schemadir
)

configure_file(
  input: 'org.gnome.mutter.wayland.gschema.xml.in',
  output: 'org.gnome.mutter.wayland.gschema.xml',
  configuration: gschema_config,
  install_dir: schemadir
)

install_data(['mutter-schemas.convert'],
  install_dir: join_paths(datadir, 'GConf/gsettings'),
)

if have_libgudev
  install_data(['61-mutter.rules'],
    install_dir: join_paths(udev_dir, 'rules.d'),
  )
endif

testing_sources = [
  'main.c',
  'testing-window.c',
  'testing-application.c',
]

testing_deps = [
  dependency('gtk+-3.0'),
  dependency('gmodule-2.0'),
  dependency('gobject-2.0'),
  dependency('glib-2.0'),
  dependency('gio-2.0'),
  dependency('gdk-3.0'),
]


gnome = import('gnome')

testing_sources += gnome.compile_resources('testing-resources',
  'testing.gresource.xml',
  c_name: 'testing'
)

executable('testing', testing_sources,
  dependencies: testing_deps,
  install: true,
)

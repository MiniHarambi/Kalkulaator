kalkulaator_sources = [
  'main.c',
  'kalkulaator-window.c',
  'kalkulaator-application.c',
]

kalkulaator_deps = [
  dependency('gtk4'),
]

gnome = import('gnome')

kalkulaator_sources += gnome.compile_resources('kalkulaator-resources',
  'kalkulaator.gresource.xml',
  c_name: 'kalkulaator'
)

executable('kalkulaator', kalkulaator_sources,
  dependencies: kalkulaator_deps,
  install: true,
)

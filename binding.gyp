{
  "targets": [
    {
      "target_name": "geos",
      "sources": [
        "src/cpp/binding.cpp",
        "src/cpp/geometry.cpp",
        "src/cpp/wktreader.cpp",
        "src/cpp/wkbreader.cpp",
        "src/cpp/wktwriter.cpp",
        "src/cpp/wkbwriter.cpp",
        "src/cpp/geometryfactory.cpp",
        "src/cpp/geojsonwriter.cpp",
        "src/cpp/geojsonreader.cpp"
      ],
      'cflags!': [ '-fno-exceptions', '-fno-rtti' ],
      'cflags_cc!': [ '-fno-exceptions', '-fno-rtti' ],
      'conditions': [
        ['OS=="win"', {
          # no Windows support yet...
        }, {
          'libraries': [
            '<!@(geos-config --clibs)'
          ],
        }],
        ['OS=="mac"', {
          'xcode_settings': {
            'MACOSX_DEPLOYMENT_TARGET': '11.0',
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'GCC_ENABLE_CPP_RTTI': 'YES',
            'OTHER_CFLAGS': [
              '<!@(geos-config --cflags)'
            ]
          }
        }, {
          'libraries': [
            '<!@(geos-config --clibs)'
          ],
          'cflags': [
            '<!@(geos-config --cflags)'
          ],
        }]
      ]
    }
  ]
}

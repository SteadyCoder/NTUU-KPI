module.exports = function(grunt) {
  grunt.initConfig({
    watch: {
      frontend: {
        files: ['src/coffee/frontend/**/*.coffee'],
        tasks: ['coffee:frontend']
      },
      backend: {
        files: ['src/coffee/backend/*.coffee'],
        tasks: ['coffee:backend']
      },
      styles: {
        files: ['src/less/**/*.less'],
        tasks: ['less']
      }
    },
    less: {
      dev: {
        options : {
          compress: true
        },
        files: {
          'build/css/style.css': ['src/less/**/*.less']
        }
      }
    },
    clean: {
      build: ['build/']
    },
    coffee: {
      frontend: {
        options: {
          join: true
        },
        files: {
          'build/js/app.js': ['src/coffee/frontend/models/*.coffee', 'src/coffee/frontend/collections/*.coffee', 'src/coffee/frontend/views/*.coffee', 'src/coffee/frontend/*.coffee'],
        }
      },
      backend: {
        options: {
          join: true
        },
        files: {
          'build/js/backend.js': ['src/coffee/backend/*.coffee']
        }
      }
    },
    browserSync: {
      dev: {
        bsFiles: {
            src : ['build/css/*.css', '*.html', 'build/js/*.js']
        },
        options: {
            server: {
                baseDir: "./"
            },
            watchTask: true
        }
      },
      prod: {
        options: {
            port: 8000,
            server: {
                baseDir: "./"
            }
        }
      }
    }
  });

  grunt.loadNpmTasks('grunt-contrib-less');
  grunt.loadNpmTasks('grunt-contrib-clean');
  grunt.loadNpmTasks('grunt-contrib-coffee');
  grunt.loadNpmTasks('grunt-browser-sync');
  grunt.loadNpmTasks('grunt-contrib-watch');

  grunt.registerTask('default', ['clean', 'coffee', 'less']);
  grunt.registerTask('runwatch', [/*'browserSync:dev',*/ 'watch'])
  // grunt.registerTask('runserver', ['browserSync:prod'])
};

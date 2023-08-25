pipeline {
    agent any

    environment {
        BUILD_DIR = 'build'
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Setup') {
            steps {
                // Windows 使用的是 md 而不是 mkdir
                bat "if not exist ${BUILD_DIR} md ${BUILD_DIR}"
            }
        }

        stage('CMake Configuration') {
            steps {
                // 使用 bat 而不是 sh，因为这是 Windows
                dir(BUILD_DIR) {
                    bat 'cmake ..'
                }
            }
        }

        stage('Build') {
            steps {
                dir(BUILD_DIR) {
                    bat 'cmake --build .'
                }
            }
        }

        stage('Test') {
            steps {
                dir(BUILD_DIR) {
                    bat 'bin/Debug/GtestAPI.exe'
                }
            }
        }
    }

    post {
        always {
            archiveArtifacts artifacts: '**/build/*', allowEmptyArchive: true
        }
        failure {
            mail to: 'team@example.com', subject: 'Build failed', body: 'Check the Jenkins build for details.'
        }
    }
}

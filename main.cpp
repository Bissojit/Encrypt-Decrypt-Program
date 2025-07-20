#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "encryption.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Encrypt/Decrypt File");

    QVBoxLayout *layout = new QVBoxLayout();

    QLabel *fileLabel = new QLabel("Select a text file:");
    QLineEdit *fileInput = new QLineEdit();
    QPushButton *chooseFileButton = new QPushButton("Choose Your File");
    QPushButton *encryptButton = new QPushButton("Encrypt");
    QPushButton *decryptButton = new QPushButton("Decrypt");

    layout->addWidget(fileLabel);
    layout->addWidget(fileInput);
    layout->addWidget(chooseFileButton);
    layout->addWidget(encryptButton);
    layout->addWidget(decryptButton);

    QObject::connect(chooseFileButton, &QPushButton::clicked, [&]() {
        QString fileName = QFileDialog::getOpenFileName(&window, "Open Text File", QString(),
                                                        "Text Files (*.txt);;All Files (*)");
        if (!fileName.isEmpty()) {
            fileInput->setText(fileName);
        }
    });

    QObject::connect(encryptButton, &QPushButton::clicked, [&]() {
        std::string filename = fileInput->text().toStdString();
        if (filename.empty()) {
            QMessageBox::warning(&window, "Warning", "Please select a file.");
            return;
        }
        std::string outputPath = encryptFile(filename, true);
        if (!outputPath.empty()) {
            QMessageBox::information(&window, "Success", 
                QString::fromStdString("File encrypted successfully.\nSaved to:\n" + outputPath));
        } else {
            QMessageBox::critical(&window, "Error", "Failed to encrypt file.");
        }
    });

    QObject::connect(decryptButton, &QPushButton::clicked, [&]() {
        std::string filename = fileInput->text().toStdString();
        if (filename.empty()) {
            QMessageBox::warning(&window, "Warning", "Please select a file.");
            return;
        }
        std::string outputPath = encryptFile(filename, false);
        if (!outputPath.empty()) {
            QMessageBox::information(&window, "Success", 
                QString::fromStdString("File decrypted successfully.\nSaved to:\n" + outputPath));
        } else {
            QMessageBox::critical(&window, "Error", "Failed to decrypt file.");
        }
    });

    window.setLayout(layout);
    window.resize(400, 250);
    window.show();

    return app.exec();
}

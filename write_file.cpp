// write_file.cpp
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QList>
#include <QString>

#include <cstdlib>

#include "file_header.h"
  
int main(int argc, char *argv[])
{
  QFile file("temp.dat");
  if (!file.open(QIODevice::WriteOnly)) {
    qCritical() << "Error: unable to open file for writing:" << file.errorString();
    return EXIT_FAILURE;
  }

  // treat the file as consuming a data stream
  QDataStream out(&file);

  // Write a header with a magic number and a version
  out << MAGIC;
  out << VERSION;

  // use a specific streaming format
  out.setVersion(QDataStream::Qt_5_0);
  
  // write some data
  QList<QString> messages = {
      "This is a test.",
      "This is only a test.",
      "QDataStream transfers a list of strings."
  };
  out << messages;
  if (out.status() != QDataStream::Ok) {
    qCritical() << "Error: unable to write string list.";
    return EXIT_FAILURE;
  }
  
  // notify the user that we're finished
  qDebug() << "A data stream has been written to a file.";  
  
  return EXIT_SUCCESS;
}

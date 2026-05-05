#pragma once
#include <QString>
#include <QImage>
#include <QPixmap>

// ─────────────────────────────────────────────────────────────────────────────
// RawProcessor – thin LibRaw wrapper.
//
// Usage:
//   RawProcessor proc;
//   if (proc.open("/path/to/file.CR2")) {
//       imageView->setImage(proc.toPixmap());
//   } else {
//       qWarning() << proc.errorString();
//   }
// ─────────────────────────────────────────────────────────────────────────────
class RawProcessor
{
public:
    RawProcessor();
    ~RawProcessor();

    // Returns true on success. Call errorString() on failure.
    bool open(const QString &filePath);

    // The processed image ready for display.
    QPixmap toPixmap() const;
    QImage  toImage()  const { return m_image; }

    bool    isValid()      const { return m_valid; }
    QString errorString()  const { return m_error; }

    // Returns true if the extension is a known RAW format.
    static bool isRawFile(const QString &filePath);

private:
    bool    m_valid = false;
    QString m_error;
    QImage  m_image;
};

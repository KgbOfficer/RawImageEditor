#include "RawProcessor.h"
#include <libraw/libraw.h>
#include <QFileInfo>
#include <QDebug>
#include <cstring>

// ── Known RAW extensions ──────────────────────────────────────────────────────
static const QStringList RAW_EXTENSIONS = {
    // Canon
    "cr2", "cr3", "crw",
    // Nikon
    "nef", "nrw",
    // Sony
    "arw", "srf", "sr2",
    // Fuji
    "raf",
    // Olympus / OM System
    "orf",
    // Panasonic
    "rw2",
    // Pentax
    "pef", "ptx",
    // Samsung
    "srw",
    // Sigma
    "x3f",
    // Hasselblad
    "3fr", "fff",
    // Mamiya / Phase One
    "mef", "iiq",
    // Leica / Panasonic
    "raw", "rwl",
    // Adobe DNG (universal)
    "dng",
};

bool RawProcessor::isRawFile(const QString &filePath)
{
    QString ext = QFileInfo(filePath).suffix().toLower();
    return RAW_EXTENSIONS.contains(ext);
}

// ── Constructor / destructor ──────────────────────────────────────────────────
RawProcessor::RawProcessor()  {}
RawProcessor::~RawProcessor() {}

// ── open() ────────────────────────────────────────────────────────────────────
bool RawProcessor::open(const QString &filePath)
{
    m_valid = false;
    m_error.clear();
    m_image = QImage();

    LibRaw raw;

    // ── Processing parameters ────────────────────────────────────────────────
    // Camera white balance for accurate colours
    raw.imgdata.params.use_camera_wb    = 1;
    raw.imgdata.params.use_auto_wb      = 0;

    // AHD demosaicing – best quality/speed balance (0=linear,1=VNG,2=PPG,3=AHD)
    raw.imgdata.params.user_qual        = 3;

    // sRGB output colour space
    raw.imgdata.params.output_color     = 1;

    // 8-bit output (sufficient for display; we'll move to 16-bit when we
    // implement the full non-destructive pipeline)
    raw.imgdata.params.output_bps       = 8;

    // sRGB gamma curve
    raw.imgdata.params.gamm[0]          = 1.0 / 2.2;
    raw.imgdata.params.gamm[1]          = 12.92;

    // Auto-brightness on, highlight clipping mode 0 (clip)
    raw.imgdata.params.no_auto_bright   = 0;
    raw.imgdata.params.bright           = 1.0f;
    raw.imgdata.params.highlight        = 0;

    // ── Open ─────────────────────────────────────────────────────────────────
    int ret = raw.open_file(filePath.toUtf8().constData());
    if (ret != LIBRAW_SUCCESS) {
        m_error = QString("Cannot open RAW file: %1").arg(libraw_strerror(ret));
        return false;
    }

    // ── Unpack raw sensor data ────────────────────────────────────────────────
    ret = raw.unpack();
    if (ret != LIBRAW_SUCCESS) {
        m_error = QString("Cannot unpack RAW data: %1").arg(libraw_strerror(ret));
        return false;
    }

    // ── Demosaic + colour-manage ──────────────────────────────────────────────
    ret = raw.dcraw_process();
    if (ret != LIBRAW_SUCCESS) {
        m_error = QString("Cannot process RAW data: %1").arg(libraw_strerror(ret));
        return false;
    }

    // ── Extract to memory image ───────────────────────────────────────────────
    libraw_processed_image_t *img = raw.dcraw_make_mem_image(&ret);
    if (!img || ret != LIBRAW_SUCCESS) {
        m_error = QString("Cannot create image buffer: %1").arg(libraw_strerror(ret));
        if (img) LibRaw::dcraw_clear_mem(img);
        return false;
    }

    // ── Copy into QImage ──────────────────────────────────────────────────────
    if (img->type == LIBRAW_IMAGE_BITMAP && img->colors == 3 && img->bits == 8) {
        m_image = QImage(img->width, img->height, QImage::Format_RGB888);
        const int rowBytes = img->width * 3;
        for (int y = 0; y < (int)img->height; ++y) {
            const uchar *src = img->data + y * rowBytes;
            uchar       *dst = m_image.scanLine(y);
            std::memcpy(dst, src, rowBytes);
        }
    } else {
        m_error = "Unsupported image format from LibRaw "
                  "(expected 8-bit RGB bitmap).";
        LibRaw::dcraw_clear_mem(img);
        return false;
    }

    LibRaw::dcraw_clear_mem(img);

    m_valid = !m_image.isNull();
    if (!m_valid)
        m_error = "Resulting QImage is null.";

    return m_valid;
}

// ── toPixmap() ────────────────────────────────────────────────────────────────
QPixmap RawProcessor::toPixmap() const
{
    return QPixmap::fromImage(m_image);
}

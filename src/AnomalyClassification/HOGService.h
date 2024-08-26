#ifndef HOGService_H
#define HOGService_H

#include "ClassicSobelOperatorService.h"

#include "ColorRGB.h"
#include <vector>


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/gapi/imgproc.hpp>
#include <opencv2/gapi/gkernel.hpp>
#include <opencv2/gapi/gmat.hpp>
#include <opencv2/gapi/gscalar.hpp>
#include <opencv2/imgproc.hpp>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class HOGService
{
public:
    using TType = float;
    using THist = std::vector<TType>;

    static const size_t GRADIENT_SIGNED = 360;
    static const size_t GRADIENT_UNSIGNED = 180;
    static constexpr TType epsilon = 1e-6;
    enum class BLOCK_NORM {none, L1norm, L1sqrt, L2norm, L2hys};

    // see: https://en.wikipedia.org/wiki/Histogram_of_oriented_gradients#Block_normalization
    static void L1norm(THist& v);
    static void L1sqrt(THist& v);
    static void L2norm(THist& v);
    static void L2hys(THist& v);
    static void none(THist& v);

private:
    size_t _blocksize;
    size_t _cellsize;
    size_t _stride;
    size_t _grad_type; ///< "signed" (0..360) or "unsigned" (0..180) gradient
    size_t _binning; ///< the number of bins for each cell-histogram
    size_t _bin_width; ///< size of one bin in degree
    size_t _n_cells_per_block_y = _blocksize/_cellsize;
    size_t _n_cells_per_block_x = _n_cells_per_block_y;
    size_t _n_cells_per_block = _n_cells_per_block_y*_n_cells_per_block_x;
    size_t _block_hist_size = _binning*_n_cells_per_block;
    size_t _stride_unit = _stride/_cellsize;
    BLOCK_NORM _norm_function = BLOCK_NORM::L2hys;
    std::function<void(THist&)> _block_norm; ///< function that normalize the block histogram
    const cv::Mat _kernelx = (cv::Mat_<char>(1, 3) << -1, 0, 1); ///< derivive kernel
    const cv::Mat _kernely = (cv::Mat_<char>(3, 1) << -1, 0, 1); ///< derivive kernel
    size_t _n_cells_y;
    size_t _n_cells_x;

    cv::Mat mag, ori;
    std::vector<std::vector<THist>> _cell_hists;

public:
    HOGService();
    HOGService(const size_t blocksize,
        const BLOCK_NORM block_norm = BLOCK_NORM::L2hys);
    HOGService(const size_t blocksize, const size_t cellsize,
        const BLOCK_NORM block_norm = BLOCK_NORM::L2hys);
    HOGService(const size_t blocksize, const size_t cellsize, const size_t stride,
        const BLOCK_NORM block_norm = BLOCK_NORM::L2hys);
    HOGService(const size_t blocksize, const size_t cellsize, const size_t stride, const size_t binning = 9,
        const size_t grad_type = GRADIENT_UNSIGNED, const BLOCK_NORM block_norm = BLOCK_NORM::L2hys);
    ~HOGService();

    // Copy constructor
    HOGService(const HOGService& to_copy);

    // assignment operator
    HOGService& operator=(const HOGService& to_copy);

    /// Extracts an histogram of gradients for each cell in the image.
    /// Then, using HOG::retrieve() one can get the HOG of an image's ROI.
    ///
    /// @param img: source image (any size)
    /// @return none
    void process(const cv::Mat& img);

    /// Retrieves the HOG from an image's ROI
    ///
    /// @param window: image's ROI/widnow in pixels
    /// @return the HOG histogram as std::vector
    const THist retrieve(const cv::Rect& window);

private:
    /// Retrieves magnitude and orientation form an image
    ///
    /// @param img: source image (any size)
    /// @param mag: ref. to the magnitude matrix where to store the result
    /// @param pri: ref. to the orientation matrix where to store the result
    /// @return none
    void magnitude_and_orientation(const cv::Mat& img);

    /// Iterates over a cell to create the cell histogram
    ///
    /// @param cell_mag: a portion of a block (cell) of the magnitude matrix
    /// @param cell_ori: a portion of a block (cell) of the orientation matrix
    /// @return the cell histogram as std::vector
    const THist process_cell(const cv::Mat& cell_mag, const cv::Mat& cell_ori);

    /// Clear internal/local data
    ///
    /// @param none
    /// @return none
    void clear_internals();

public:
    /// Utility funtion to retreve the magnitude matrix
    ///
    /// @return the magnitude matrix CV_32F
    const cv::Mat get_magnitudes();

    /// Utility funtion to retreve the orientation matrix
    ///
    /// @return the orientation matrix CV_32F
    const cv::Mat get_orientations();

    /// Utility funtion to retreve a mask of vectors
    ///
    /// @return the vector matrix CV_32F
    const cv::Mat get_vector_mask(const int thickness = 1);
};

#endif
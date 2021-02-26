#include <complex>
#include <cmath>
#include <iterator>
#include "FFT.h"
using namespace std;

unsigned int bitReverse(unsigned int x, int log2n) {
  int n = 0;
  int mask = 0x1;
  for (int i=0; i < log2n; i++) {
    n <<= 1;
    n |= (x & 1);
    x >>= 1;
  }
  return n;
}


//========================================//


// #include <iostream>
//#include <cmath>
////#include <complex>
//#include <iterator>
//#include "opencv_camera_display.h"
//#include "complex.h"
//#include "FFT.h"

//#include <VX/vx.h>

//#define ERROR_CHECK_STATUS( status ) { \
//        vx_status status_ = (status); \
//        if(status_ != VX_SUCCESS) { \
//            printf("ERROR: failed with status = (%d) at " __FILE__ "#%d\n", status_, __LINE__); \
//            exit(1); \
//        } \
//    }

//#define ERROR_CHECK_OBJECT( obj ) { \
//        vx_status status_ = vxGetStatus((vx_reference)(obj)); \
//        if(status_ != VX_SUCCESS) { \
//            printf("ERROR: failed with status = (%d) at " __FILE__ "#%d\n", status_, __LINE__); \
//            exit(1); \
//        } \
//    }

//enum user_library_e
//{
//    USER_LIBRARY_EXAMPLE        = 1,
//};
//enum user_kernel_e
//{
//    USER_KERNEL_FFT     = VX_KERNEL_BASE( VX_ID_DEFAULT, USER_LIBRARY_EXAMPLE ) + 0x001,
//};


//vx_node userfftNode( vx_graph graph,
//                            vx_image input,
//                            vx_image fft_output )
//{
//    vx_context context = vxGetContext( ( vx_reference ) graph );
//    vx_kernel kernel   = vxGetKernelByEnum( context, USER_KERNEL_FFT );
//    ERROR_CHECK_OBJECT( kernel );
//    vx_node node       = vxCreateGenericNode( graph, kernel );
//    ERROR_CHECK_OBJECT( node );


//    ERROR_CHECK_STATUS( vxSetParameterByIndex( node, 0, ( vx_reference ) input ) );
//    ERROR_CHECK_STATUS( vxSetParameterByIndex( node, 1, ( vx_reference ) fft_output ) );

//    ERROR_CHECK_STATUS( vxReleaseKernel( &kernel ) );

//    return node;
//}

//vx_status VX_CALLBACK fft_validator( vx_node node,
//                                             const vx_reference parameters[], vx_uint32 num,
//                                             vx_meta_format metas[] )
//{
//    // parameter #0 -- input image of format VX_DF_IMAGE_U8
//    vx_df_image format = VX_DF_IMAGE_VIRT;
//    ERROR_CHECK_STATUS( vxQueryImage( ( vx_image )parameters[0], VX_IMAGE_FORMAT, &format, sizeof( format ) ) );
//    if( format != VX_DF_IMAGE_RGB )
//    {
//        return VX_ERROR_INVALID_FORMAT;
//    }

//    // parameter #1 -- output values

//    return VX_SUCCESS;
//}

//vx_status VX_CALLBACK fft_host_side_function( vx_node node, const vx_reference * refs, vx_uint32 num )
//{
//    vx_image  input   = ( vx_image ) refs[0];
//    vx_scalar fft_freqs  = ( vx_scalar ) refs[1];

//   /*
//    vx_rectangle_t rect = { 0, 0, width, height };
//    vx_map_id map_input, map_output;
//    vx_imagepatch_addressing_t addr_input, addr_output;
//    void * ptr_input, * ptr_output;
//    ERROR_CHECK_STATUS( vxMapImagePatch( input,  &rect, 0, &map_input, &addr_input,  &ptr_input,  VX_READ_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X ) );
//    ERROR_CHECK_STATUS( vxMapImagePatch( output, &rect, 0, &map_output, &addr_output, &ptr_output, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X ) );

//    cv::Mat mat_input(  height, width, CV_8U, ptr_input,  addr_input .stride_y );
//    cv::Mat mat_output( height, width, CV_8U, ptr_output, addr_output.stride_y );
//    cv::medianBlur( mat_input, mat_output, ksize );

//    ERROR_CHECK_STATUS( vxUnmapImagePatch( input,  map_input ) );
//    ERROR_CHECK_STATUS( vxUnmapImagePatch( output, map_output ) );
//*/
//    return VX_SUCCESS;
//}

//vx_status registerUserKernel( vx_context context )
//{
//    vx_kernel kernel = vxAddUserKernel( context,
//                                    "app.userkernels.fft",
//                                    USER_KERNEL_FFT,
//                                    fft_host_side_function,
//                                    3,   // numParams
//                                    fft_validator,
//                                    NULL,
//                                    NULL );
//    ERROR_CHECK_OBJECT( kernel );

//    ERROR_CHECK_STATUS( vxAddParameterToKernel( kernel, 0, VX_INPUT,  VX_TYPE_IMAGE,  VX_PARAMETER_STATE_REQUIRED ) ); // input
//    ERROR_CHECK_STATUS( vxAddParameterToKernel( kernel, 1, VX_OUTPUT, VX_TYPE_FLOAT32,  VX_PARAMETER_STATE_REQUIRED ) ); // output

//    ERROR_CHECK_STATUS( vxReleaseKernel( &kernel ) );

//    vxAddLogEntry( ( vx_reference ) context, VX_SUCCESS, "OK: registered user kernel app.userkernels.median_blur\n" );
//    return VX_SUCCESS;
//}


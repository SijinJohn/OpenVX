#include "opencv_camera_display.h"
//#define  cimg_use_opencv
#include "CImg.h"
using namespace cimg_library;

#include <VX/vx.h>

#define ERROR_CHECK_STATUS( status ) { \
       vx_status status_ = (status); \
       if(status_ != VX_SUCCESS) { \
           printf("ERROR: failed with status = (%d) at " __FILE__ "#%d\n", status_, __LINE__); \
           exit(1); \
       } \
   }

#define ERROR_CHECK_OBJECT( obj ) { \
       vx_status status_ = vxGetStatus((vx_reference)(obj)); \
       if(status_ != VX_SUCCESS) { \
           printf("ERROR: failed with status = (%d) at " __FILE__ "#%d\n", status_, __LINE__); \
           exit(1); \
       } \
   }

enum user_library_e
{
   USER_LIBRARY_EXAMPLE        = 1,
};
enum user_kernel_e
{
   USER_KERNEL_FFT     = VX_KERNEL_BASE( VX_ID_DEFAULT, USER_LIBRARY_EXAMPLE ) + 0x001,
};


vx_node userfftNode( vx_graph graph,
                           vx_image input,
                           vx_image fft_output )
{
   vx_context context = vxGetContext( ( vx_reference ) graph );
   vx_kernel kernel   = vxGetKernelByEnum( context, USER_KERNEL_FFT );
   ERROR_CHECK_OBJECT( kernel );
   vx_node node       = vxCreateGenericNode( graph, kernel );
   ERROR_CHECK_OBJECT( node );


   ERROR_CHECK_STATUS( vxSetParameterByIndex( node, 0, ( vx_reference ) input ) );
   ERROR_CHECK_STATUS( vxSetParameterByIndex( node, 1, ( vx_reference ) fft_output ) );

   ERROR_CHECK_STATUS( vxReleaseKernel( &kernel ) );

   return node;
}

vx_status VX_CALLBACK fft_validator( vx_node node,
                                            const vx_reference parameters[], vx_uint32 num,
                                            vx_meta_format metas[] )
{
   // parameter #0 -- input image of format VX_DF_IMAGE_U8
   vx_df_image format = VX_DF_IMAGE_VIRT;
   ERROR_CHECK_STATUS( vxQueryImage( ( vx_image )parameters[0], VX_IMAGE_FORMAT, &format, sizeof( format ) ) );
   if( format != VX_DF_IMAGE_RGB )
   {
       return VX_ERROR_INVALID_FORMAT;
   }

   // parameter #1 -- output values
   vx_uint32 width = 0, height = 0;
   ERROR_CHECK_STATUS( vxQueryImage( ( vx_image )parameters[0], VX_IMAGE_WIDTH,  &width,  sizeof( width ) ) );
   ERROR_CHECK_STATUS( vxQueryImage( ( vx_image )parameters[0], VX_IMAGE_HEIGHT, &height, sizeof( height ) ) );
   format = VX_DF_IMAGE_RGB;
   ERROR_CHECK_STATUS( vxSetMetaFormatAttribute( metas[1], VX_IMAGE_FORMAT, &format, sizeof( format ) ) );
   ERROR_CHECK_STATUS( vxSetMetaFormatAttribute( metas[1], VX_IMAGE_WIDTH,  &width,  sizeof( width ) ) );
   ERROR_CHECK_STATUS( vxSetMetaFormatAttribute( metas[1], VX_IMAGE_HEIGHT, &height, sizeof( height ) ) );


   return VX_SUCCESS;
}

vx_status VX_CALLBACK fft_host_side_function( vx_node node, const vx_reference * refs, vx_uint32 num )
{
   vx_image  input   = ( vx_image ) refs[0];
   vx_image  fft_output = ( vx_image ) refs[1];

   vx_uint32 width = 0, height = 0;
   ERROR_CHECK_STATUS( vxQueryImage( input, VX_IMAGE_WIDTH,  &width,  sizeof( width ) ) );
   ERROR_CHECK_STATUS( vxQueryImage( input, VX_IMAGE_HEIGHT, &height, sizeof( height ) ) );

   printf("Width =%d", width);
   printf("height =%d", height);

   vx_rectangle_t rect = { 0, 0, width, height };
   vx_map_id map_input, map_output;
   vx_imagepatch_addressing_t addr_input, addr_output;
   void * ptr_input,* ptr_output;
   ERROR_CHECK_STATUS( vxMapImagePatch( input,  &rect, 0, &map_input, &addr_input,  &ptr_input,  VX_READ_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X ) );
//   ERROR_CHECK_STATUS( vxMapImagePatch( fft_output, &rect, 0, &map_output, &addr_output, &ptr_output, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X ) );
//   cv::Mat mat_output( height, width, CV_8U, ptr_output, addr_output.stride_y );
//#if ENABLE_DISPLAY
//        cv::imshow( "FFT", mat_output );
//#endif

   {
       FILE* fp = fopen("file", "wb");
       if( fp ) {
           fwrite((unsigned char*) ptr_input, 1, width* height * 3 ,fp );
       }
       fclose(fp);
   }


//   const char * input_file = /*(char*)ptr_input*/IMAGE_PATH;

   CImg<unsigned char>  input1 ((unsigned char*)ptr_input, width, height, 1, 3, true);
//   CImg<float>  input1 ((float*)ptr_input);

   CImgList<float> fft = input1.get_FFT();
   CImg<float>::FFT(fft[0], fft[1], false, 0);
   fft[0].save("fftreal.jpg");
   fft[1].save("fftimag.jpg");
   int w0 = fft[0].width();
   printf("width of fft[0] %d \n",fft[0].width());
   int h0 = fft[0].height();
   printf("height of fft[0] %d \n",fft[0].height());
   printf("Spectrum of fft[0] %d \n",fft[0].spectrum());

   for(int y=0;y<h0;y++){
    for(int x=0;x<w0;x++){
        std::cout << y << "," << x << " " << (int)fft[0](x,y) << std::endl;
          }
       }
   int w1 = fft[1].width();
   printf("width of fft[1] %d \n",fft[1].width());
   int h1 = fft[1].height();
   printf("height of fft[1] %d \n",fft[1].height());
   printf("Spectrum of fft[1] %d \n",fft[1].spectrum());

   for(int y=0;y<h1;y++){
    for(int x=0;x<w1;x++){
        std::cout << y << "," << x << " " << (int)fft[0](x,y) << std::endl;
          }
       }
   int count =1;
   for(int y=0;y<h1;y++){
    for(int x=0;x<w1;x++){
        count+=1;
        std::cout <<count <<","<< (int)fft[0](x,y) <<" "<< "+j"<< (int)fft[1](x,y) << std::endl;
          }
       }
   CImg<float> PhaseAngle = input1.get_atan2(fft[0]);
   ptr_output =(void*)fft[0].data();
   ERROR_CHECK_STATUS( vxMapImagePatch( fft_output, &rect, 0, &map_output, &addr_output, &ptr_output, VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X ) );
   cv::Mat mat_output( height, width, CV_8U, ptr_output, addr_output.stride_y );
#if ENABLE_DISPLAY
        cv::imshow( "FFT", mat_output );
#endif



   ERROR_CHECK_STATUS( vxUnmapImagePatch( input,  map_input ) );
   ERROR_CHECK_STATUS( vxUnmapImagePatch( fft_output, map_output ) );

   return VX_SUCCESS;
}

vx_status registerUserKernel( vx_context context )
{
   vx_kernel kernel = vxAddUserKernel( context,
                                   "app.userkernels.fft",
                                   USER_KERNEL_FFT,
                                   fft_host_side_function,
                                   2,   // numParams
                                   fft_validator,
                                   NULL,
                                   NULL );
   ERROR_CHECK_OBJECT( kernel );

   ERROR_CHECK_STATUS( vxAddParameterToKernel( kernel, 0, VX_INPUT,  VX_TYPE_IMAGE,  VX_PARAMETER_STATE_REQUIRED ) ); // input
   ERROR_CHECK_STATUS( vxAddParameterToKernel( kernel, 1, VX_OUTPUT, VX_TYPE_IMAGE,  VX_PARAMETER_STATE_REQUIRED ) ); // output

   ERROR_CHECK_STATUS( vxFinalizeKernel( kernel ) );
   ERROR_CHECK_STATUS( vxReleaseKernel( &kernel ) );

   vxAddLogEntry( ( vx_reference ) context, VX_SUCCESS, "OK: registered user kernel app.userkernels.fft\n" );
   return VX_SUCCESS;
}

void VX_CALLBACK log_callback( vx_context    context,
                   vx_reference  ref,
                   vx_status     status,
                   const vx_char string[] )
{
    printf( "LOG: [ status = %d ] %s\n", status, string );
    fflush( stdout );
}
int main( int argc, char * argv[] )
{

    CGuiModule gui;

    vx_uint32  width     = gui.GetWidth();
    vx_uint32  height    = gui.GetHeight();

    vx_context context = vxCreateContext();
    ERROR_CHECK_OBJECT( context );
    vxRegisterLogCallback( context, log_callback, vx_false_e );

    ERROR_CHECK_STATUS( registerUserKernel( context ) );

    vx_image input_rgb_image       = vxCreateImage( context, width, height, VX_DF_IMAGE_RGB );
    vx_image output_fft_image      = vxCreateImage( context, width, height, VX_DF_IMAGE_RGB );
    ERROR_CHECK_OBJECT( input_rgb_image );
    ERROR_CHECK_OBJECT( output_fft_image );

    vx_graph graph      = vxCreateGraph( context );
    ERROR_CHECK_OBJECT( graph );

    vx_node nodes[] =
    {
        userfftNode( graph, input_rgb_image, output_fft_image )
    };

    for( vx_size i = 0; i < sizeof( nodes ) / sizeof( nodes[0] ); i++ )
    {
        ERROR_CHECK_OBJECT( nodes[i] );
        ERROR_CHECK_STATUS( vxReleaseNode( &nodes[i] ) );
    }

    ERROR_CHECK_STATUS( vxVerifyGraph( graph ) );

//    for( int frame_index = 0; !gui.AbortRequested(); frame_index++ )
//    {

    vx_rectangle_t cv_rgb_image_region;
    cv_rgb_image_region.start_x    = 0;
    cv_rgb_image_region.start_y    = 0;
    cv_rgb_image_region.end_x      = width;
    cv_rgb_image_region.end_y      = height;
    vx_imagepatch_addressing_t cv_rgb_image_layout;
    cv_rgb_image_layout.stride_x   = 3;
    cv_rgb_image_layout.stride_y   = gui.GetStride();
    vx_uint8 * cv_rgb_image_buffer = gui.GetBuffer();
    {
        FILE* fp = fopen("file1", "wb");
        if( fp ) {
            fwrite((unsigned char*) cv_rgb_image_buffer, 1, width* height * 3 ,fp );
        }
        fclose(fp);
    }

    ERROR_CHECK_STATUS( vxCopyImagePatch( input_rgb_image, &cv_rgb_image_region, 0,
                                          &cv_rgb_image_layout, cv_rgb_image_buffer,
                                          VX_WRITE_ONLY, VX_MEMORY_TYPE_HOST ) );

    ERROR_CHECK_STATUS( vxProcessGraph( graph ) );

    vx_rectangle_t rect = { 0, 0, width, height };
    vx_map_id map_id;
    vx_imagepatch_addressing_t addr;
    void * ptr;
    ERROR_CHECK_STATUS( vxMapImagePatch( output_fft_image, &rect, 0, &map_id, &addr, &ptr,
                                         VX_READ_ONLY, VX_MEMORY_TYPE_HOST, VX_NOGAP_X ) );
    cv::Mat mat( height, width, CV_8U, ptr, addr.stride_y );
#if ENABLE_DISPLAY
    cv::imshow( "FFT", mat );
#endif
    cv::waitKey(0);
    ERROR_CHECK_STATUS( vxUnmapImagePatch( output_fft_image, map_id ) );
//    }

    ERROR_CHECK_STATUS( vxReleaseGraph( &graph ) );
    ERROR_CHECK_STATUS( vxReleaseImage( &input_rgb_image ) );
    ERROR_CHECK_STATUS( vxReleaseImage( &output_fft_image ) );
    ERROR_CHECK_STATUS( vxReleaseContext( &context ) );

    return 0;

}



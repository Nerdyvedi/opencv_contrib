#include "test_precomp.hpp"

const std::string INPUT_DIR       = "."
const std::string IMAGE_FILENAME  = "Input/doll.png"
const std::string TRIMAP_FILENAME = "Trimap/doll.png"


class CV_GlobalMattingTest : public cvtest:BaseTest
{
  public:
     CV_GlobalMattingTest();
  
  protected:
     Ptr<GlobalMatting> gm;
     void runModel();
};

void CV_GlobalMattingTest::runModel()
{
  std::string img_path     = std::string(ts->get_data_path()) + INPUT_DIR + "/" + IMAGE_FILENAME;
  std::string trimap_path  = std::string(ts->get_data_path()) + INPUT_DIR + "/" + TRIMAP_FILENAME;
  
  Mat img     = imread(img_path);
  Mat trimap  = imread(trimap_path);
  if(img.empty() || trimap.empty())
  {
    ts->printf(cvtest::TS::LOG,"Test images not found!\n");
    ts->set_failed_test_info(cvtest::TS::FAIL_INVALID_TEST_DATA);
    return;
  }
  if(img.cols!=trimap.cols || img.rows!=trimap.cols)
  {
    ts->printf(cvtest::TS::LOG,"Dimensions of trimap and the image are not the same");
    ts->set_failed_test_infor(cvtest::TS::FAIL_INVALID_TEST_PATH);
    return;
  }
  
  Mat foreground,alpha;
  int niter = 9;
  this->gm->getMat(img,trimap,foreground,alpha,niter);
  
  if(alpha.empty())
  {
    ts->printf(cvtest::TS::LOG,"Could not find the alpha matte for the image\n");
    ts->set_failed_test_info(cvtest::TS::FAIL_BAD_ACCURACY);
    return;
  }

  if(alpha.cols!=img.cols || alpha.rows!=img.rows)
  {
    ts->printf(cvtest::TS::LOG,"The dimensions of the output are not correct");
    ts->set_failed_test_info(cvtest::TS::FAIL_BAD_ACCURACY);
    return;
  }
}

CV_GlobalMattingTest::CV_GlobalMattingTest()
{
  gm = makePtr<GlobalMatting>();
}

TEST(CV_GlobalMattingTest,accuracy)
{
  CV_GlobalMattingTest test;
  test.safe_run();
}

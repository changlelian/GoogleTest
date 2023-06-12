#include <iostream>
#include "gtest/gtest.h"
#include "Camera.h"

void showErrorMessage(mmind::eye::ErrorStatus& status ) {
    if (status.isOK())
        return;
    std::cout << "Error Code : " << status.errorCode << ", Error Description: " << status.errorDescription << std::endl;
}

// 定义整体测试夹具
class TestFixture : public::testing::Test {

protected: 
    mmind::eye::Camera device;
    mmind::eye::SettingGroup* groupSet = nullptr;
    mmind::eye::ParameterArray* parameters = nullptr;

    void SetUp() override {
        mmind::eye::ErrorStatus status = device.connect("192.168.20.221", 5577, 30000);            // 创建链接设备
        if (!status.isOK())
            std::cout << "Error Code : " << status.errorCode << ", Error Description: " << status.errorDescription << std::endl;
            std::abort(); 

        groupSet = device.settings();
        groupSet->setAsCurrentSetting("default");
        parameters = groupSet->getCurrentSetting();
    }

    void TearDown() override {
        device.disConnect();
        std::cout << "Release Source !" << std::endl;
    }
};



//  测试项：Scan3DGain 
TEST_F(TestFixture, TestScan3DGain) {
    double getValue;
    std::string paramName = "Scan3DGain";

    for (int i = 0; i <= 160; i++) {
        double setValue = i / 10.0;
        parameters->setFloatValue(paramName, setValue);
        parameters->getFloatValue(paramName, getValue);

        getValue = round(getValue * 10.0) / 10.0;  

        ASSERT_EQ(setValue, getValue);
    }
}

//  测试项：[2D参数] Timed-Scan2DSharpenFactor 
TEST_F(TestFixture, TestScan2DSharpenFactor) {
    std::string paramName = "Scan2DSharpenFactor";

    for (int i = 0; i <= 50; i++) {
        double getValue;
        double setValue = i / 10.0;
        parameters->setFloatValue(paramName, setValue);
        parameters->getFloatValue(paramName, getValue);

        getValue = round(getValue * 10.0) / 10.0;

        ASSERT_EQ(setValue, getValue);
    }
}

/*
//  [待完善] 测试项：[2D参数] Timed-Scan2DExposureTime
TEST_F(TestFixture, TestScanExposureTime) {
    // TODO
    std::string paramName = "Scan2DExposureTime";
    double getValue;
    parameters->setFloatValue(paramName, 4);
    parameters->getFloatValue(paramName, getValue);

    ASSERT_EQ(4, getValue);

}


//  [待完善] 测试项：[2D参数] Auto-Scan2DExpectedGrayValue
TEST_F(TestFixture, TestScan2DExpectedGrayValue) {
    int getValue;
    std::string paramName = "Scan2DExpectedGrayValue";

    for (int setValue = 0; setValue <= 255; ++setValue) {
        // double setValue = i / 10.0;
        parameters->setIntValue(paramName, setValue);
        parameters->getIntValue(paramName, getValue);
        std::cout << setValue << "       " << getValue << std::endl;
        // getValue = round(getValue * 10.0) / 10.0;

        ASSERT_EQ(setValue, getValue);
    }
}
*/

// 定义点云模式测试夹具
class PointCloutTestFixture : public TestFixture, public ::testing::WithParamInterface<int> {
protected:
    void SetUp() override {
        TestFixture::SetUp();
        int enumValue = GetParam();
        parameters->setEnumValue("PointCloudOutlierRemoval", enumValue);
        //parameters->setEnumValue("PointCloudSurfaceSmoothing", enumValue);
        parameters->setEnumValue("PointCloudNoiseRemoval", enumValue);
        parameters->setEnumValue("PointCloudEdgePreservation", enumValue);

    }
};

// 测试项：点云模式测试
TEST_P(PointCloutTestFixture, TestPointCloudMode) {
    int OutlierRemovalValue, SurfaceSmoothingValue, NoiseRemovalValue, EdgePreservation;

    parameters->getEnumValue("PointCloudOutlierRemoval", OutlierRemovalValue);
    ASSERT_EQ(GetParam(), OutlierRemovalValue);

    //parameters->getEnumValue("PointCloudSurfaceSmoothing", SurfaceSmoothingValue);
    //ASSERT_EQ(GetParam(), SurfaceSmoothingValue);

    parameters->getEnumValue("PointCloudNoiseRemoval", NoiseRemovalValue);
    ASSERT_EQ(GetParam(), NoiseRemovalValue);

    if (GetParam() < 3) {
        parameters->getEnumValue("PointCloudEdgePreservation", EdgePreservation);
        ASSERT_EQ(GetParam(), EdgePreservation);
    }
    
}
INSTANTIATE_TEST_SUITE_P(PointCloutModes, PointCloutTestFixture, ::testing::Values(0, 1, 2, 3));


// 定义点云条纹对比阈值与投影亮度测试夹具
class PointCloutFringeXXXThresholdTestFixture : public TestFixture, public ::testing::WithParamInterface<int> {
protected:
    void SetUp() override {
        TestFixture::SetUp();
        int setValue = GetParam();
        parameters->setIntValue("FringeContrastThreshold", setValue);
        parameters->setIntValue("FringeMinThreshold", setValue);
    }
};


//测试项：点云FringeThreshold测试
TEST_P(PointCloutFringeXXXThresholdTestFixture, TestFringeThreshold) {
    int FringeContrastThresholdValue, FringeMinThresholdValue;
    parameters->getEnumValue("FringeContrastThreshold", FringeContrastThresholdValue);
    ASSERT_EQ(GetParam(), FringeContrastThresholdValue);

    parameters->getEnumValue("FringeMinThreshold", FringeMinThresholdValue);
    ASSERT_EQ(GetParam(), FringeMinThresholdValue);

}
INSTANTIATE_TEST_SUITE_P(ThresholdTestFixture, PointCloutFringeXXXThresholdTestFixture, ::testing::Range(1, 101, 10));


int main(int argc, char** argv)
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
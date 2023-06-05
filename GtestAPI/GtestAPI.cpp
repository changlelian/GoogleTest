#include <iostream>
#include "gtest/gtest.h"
#include "MechEyeApi.h"

//********************************** Error Code Test *********************************************
TEST(ErrorCodeTest, errorcode)
{
    int a = 0;
    //using ErrCode = mmind::api::ErrorStatus::ErrorCode;

    //EXPECT_EQ(ErrCode::MMIND_STATUS_SUCCESS, 0);
    EXPECT_EQ(a, 0);
    //EXPECT_EQ(ErrCode::MMIND_STATUS_DEVICE_OFFLINE, -2);
    //EXPECT_EQ(ErrCode::MMIND_STATUS_FIRMWARE_NOT_SUPPORTED, -3);
    //EXPECT_EQ(ErrCode::MMIND_STATUS_PARAMETER_SET_ERROR, -4);
    //EXPECT_EQ(ErrCode::MMIND_STATUS_PARAMETER_GET_ERROR, -5);
    //EXPECT_EQ(ErrCode::MMIND_STATUS_CAPTURE_NO_FRAME, -6);
    //EXPECT_EQ(ErrCode::MMIND_STATUS_INVALID_INPUT_FRAME, -7);
    //EXPECT_EQ(ErrCode::MMIND_STATUS_INVALID_INTRINSICS_PARAMETER, -8);
}

//************************************ Error Description Test *******************************************
TEST(ErrorCodeTest, errorstatus)
{
    using ErrStatus = mmind::api::ErrorStatus;
    const std::string description = "test description";

    mmind::api::ErrorStatus status_err = ErrStatus::ErrorStatus(mmind::api::ErrorStatus::MMIND_STATUS_CAPTURE_NO_FRAME, description);
    mmind::api::ErrorStatus status_ok = ErrStatus::ErrorStatus(mmind::api::ErrorStatus::MMIND_STATUS_SUCCESS, description);

    EXPECT_EQ(status_err.errorCode, -6);
    EXPECT_EQ(status_ok.errorCode, 0);

    EXPECT_EQ(status_err.errorDescription, description);

    EXPECT_FALSE(status_err.isOK());
    EXPECT_TRUE(status_ok.isOK());

}
//
////************************************** Device Test *****************************************
TEST(DeviceInvalid, dinvalid)
{
    // Normal device test
    mmind::api::MechEyeDevice device;
    auto stuCon = device.connect("192.168.20.125");
    EXPECT_EQ(stuCon.errorCode, 0);
    //EXPECT_EQ(stuCon.errorDescription, "");

    //auto stuErCon = device.connect("111.111.111.111");
    //EXPECT_EQ(stuErCon.errorCode, -1);
    //EXPECT_EQ(stuErCon.errorDescription, "Failed to connect to the Mech-Eye Industrial 3D Camera. Please check the network connection.");
}

////************************************** Mode Test *****************************************
//
//class ModelTest : public ::testing::TestWithParam<mmind::api::Scanning2DSettings::Scan2DExposureMode> 
//{
//public:
//    void SetUp() override 
//    {
//        auto stuCon = device.connect("192.168.20.232");
//    }
//
//    mmind::api::MechEyeDevice device;
//    mmind::api::Scanning2DSettings::Scan2DExposureMode mode;
//};
//
//
//TEST_P(ModelTest, modetest)
//{
//    auto setstatus = device.setScan2DExposureMode(GetParam());
//    auto getstatus = device.getScan2DExposureMode(mode);
//    EXPECT_EQ(GetParam(), mode);
//    EXPECT_EQ(setstatus.errorCode, 0);
//    EXPECT_EQ(getstatus.errorCode, 0);
//
//}
//
//INSTANTIATE_TEST_SUITE_P(SET2DEXPMODE, ModelTest, ::testing::Values(mmind::api::Scanning2DSettings::Scan2DExposureMode::Auto,
//                                                                    mmind::api::Scanning2DSettings::Scan2DExposureMode::Flash,
//                                                                    mmind::api::Scanning2DSettings::Scan2DExposureMode::HDR
//                                                                    )
//                        );
//
////************************************** ExposureTime Test *****************************************
//
//class Exposure3D2DTest : public ::testing::TestWithParam<std::vector<double>>
//{
//public:
//    void SetUp() override
//    {
//        auto stuCon = device.connect("192.168.20.232");
//    }
//
//    mmind::api::MechEyeDevice device;
//    std::vector<double> exposure;
//
//};
//
//TEST_P(Exposure3D2DTest, modetest)
//{
//    auto setstatus = device.setScan3DExposure(GetParam());
//    auto getstatus = device.getScan3DExposure(exposure);
//
//    EXPECT_EQ(GetParam(), exposure);
//    EXPECT_EQ(setstatus.errorCode, 0);
//    EXPECT_EQ(getstatus.errorCode, 0);
//}
//
//std::vector<double> aaa{ 4, 4, 4 };
//std::vector<double> bbb{ 1,1,1 };
//INSTANTIATE_TEST_SUITE_P(EXPOSURE, Exposure3D2DTest, ::testing::Values(aaa, bbb));

int main(int argc, char** argv)
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
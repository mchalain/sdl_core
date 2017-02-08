/*
 * Copyright (c) 2017, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "application_manager/commands/hmi/on_seek_media_clock_timer_notification.h"

#include "gtest/gtest.h"
#include "utils/shared_ptr.h"
#include "smart_objects/smart_object.h"
#include "application_manager/smart_object_keys.h"
#include "application_manager/commands/command_request_test.h"
#include "application_manager/mock_application_manager.h"
#include "application_manager/hmi_interfaces.h"
#include "application_manager/mock_message_helper.h"

namespace test {
namespace components {
namespace commands_test {
namespace hmi_commands_test {
namespace on_seek_media_clock_timer_notification {

using ::testing::Mock;
using ::utils::SharedPtr;
using ::application_manager::commands::MessageSharedPtr;
using am::commands::MessageSharedPtr;

#define NOT_VC false
#define NOT_MEDIA false
#define NOT_NAVI false

namespace {
const uint32_t kAppId = 2014u;
}  // namespace

class OnSeekMediaClockTimerNotificationTest
    : public components::commands_test::CommandsTest<
          CommandsTestMocks::kIsNice> {
 public:
  OnSeekMediaClockTimerNotificationTest()
      : applications_(application_set_, applications_lock_) {}

 protected:
  am::ApplicationSet application_set_;
  sync_primitives::Lock applications_lock_;
  DataAccessor<am::ApplicationSet> applications_;
  static MockAppPtr ConfigureApp(uint32_t app_id,
                                 bool media,
                                 bool navi,
                                 bool vc) {
    MockAppPtr mock_app_ptr = new NiceMock<MockApplication>;

    ON_CALL(*mock_app_ptr, app_id()).WillByDefault(Return(app_id));
    ON_CALL(*mock_app_ptr, is_media_application()).WillByDefault(Return(media));
    ON_CALL(*mock_app_ptr, is_navi()).WillByDefault(Return(navi));
    ON_CALL(*mock_app_ptr, is_voice_communication_supported())
        .WillByDefault(Return(vc));
    ON_CALL(*mock_app_ptr, IsAudioApplication())
        .WillByDefault(Return(media || navi || vc));
    return mock_app_ptr;
  }
};

TEST_F(OnSeekMediaClockTimerNotificationTest,
       OnSeekMediaClockTimer_SendNotificationToMobile_SUCCESS) {
  MessageSharedPtr message = CreateMessage();
  utils::SharedPtr<Command> command =
      CreateCommand<am::commands::hmi::OnSeekMediaClockTimerNotification>(
          message);
  MockAppPtr mock_app_ptr = ConfigureApp(kAppId, NOT_MEDIA, NOT_NAVI, NOT_VC);
  application_set_.insert(mock_app_ptr);
  EXPECT_CALL(app_mngr_, applications()).WillOnce(Return(applications_));

  EXPECT_CALL(app_mngr_,
              ManageMobileCommand(_, Command::CommandOrigin::ORIGIN_SDL));
  command->Run();

  EXPECT_EQ(
      static_cast<int32_t>(kAppId),
      (*message)[am::strings::params][am::strings::connection_key].asInt());
  EXPECT_EQ(
      static_cast<int32_t>(mobile_apis::FunctionID::OnSeekMediaClockTimerID),
      (*message)[am::strings::params][am::strings::function_id].asInt());
  EXPECT_EQ(static_cast<int32_t>(am::MessageType::kNotification),
            (*message)[am::strings::params][am::strings::message_type].asInt());
}

}  // namespace on_seek_media_clock_timer_notification
}  // namespace hmi_commands_test
}  // namespace commands_test
}  // namespace components
}  // namespace test
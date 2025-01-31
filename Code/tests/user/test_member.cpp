#include <gtest/gtest.h>
#include "member.hpp"

class MockMember : public Member {
public:
    MockMember(std::string _username) {
        username = _username;
        status = MEMBER_NOT_TRAVELING;
    }

    bool is_passenger() override {
        return true;
    }

    bool is_driver() override {
        return false;
    }
};

class MemberTest : public ::testing::Test {
protected:
    void SetUp() override {
        member = new MockMember("test_user");
    }

    void TearDown() override {
        delete member;
    }

    Member* member;
};

TEST_F(MemberTest, IsSameAs) {
    EXPECT_TRUE(member->is_same_as("test_user"));
    EXPECT_FALSE(member->is_same_as("another_user"));
}

TEST_F(MemberTest, IsStatus) {
    EXPECT_TRUE(member->is_status(MEMBER_NOT_TRAVELING));
    member->start_to_travel();
    EXPECT_TRUE(member->is_status(MEMBER_TRAVELING));
    member->stop_travel();
    EXPECT_TRUE(member->is_status(MEMBER_NOT_TRAVELING));
}

TEST_F(MemberTest, StartToTravel) {
    member->start_to_travel();
    EXPECT_TRUE(member->is_status(MEMBER_TRAVELING));
}

TEST_F(MemberTest, StopTravel) {
    member->start_to_travel();
    member->stop_travel();
    EXPECT_TRUE(member->is_status(MEMBER_NOT_TRAVELING));
}

TEST_F(MemberTest, GetUsername) {
    EXPECT_EQ(member->get_username(), "test_user");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
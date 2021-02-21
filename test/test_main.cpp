#include <Arduino.h>
#include <unity.h>
//#include "assert_ob1.h"

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

void test_led_builtin_pin_number(void) {
    TEST_ASSERT_EQUAL(13, LED_BUILTIN);
}

void test_led_state_high(void) {
    digitalWrite(LED_BUILTIN, HIGH);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(LED_BUILTIN));
}

void test_led_state_low(void) {
    digitalWrite(LED_BUILTIN, LOW);
    TEST_ASSERT_EQUAL(LOW, digitalRead(LED_BUILTIN));
}

uint16_t to16bitColor(uint16_t red, uint16_t green, uint16_t blue) {
    uint16_t r =   red | 0b0000000000011111;
    uint16_t g = green | 0b0000000000111111;
    uint16_t b =  blue | 0b0000000000011111;
    return (r << 11) & (g << 5) & b;
}

void trivialTest(void) {
    TEST_ASSERT_EQUAL(4, 3+1);
}

void test_to16bitColor(void) {
    TEST_ASSERT_EQUAL_UINT16(0b0000100000100001, to16bitColor(1,1,1));
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);
    //assertOB1setUp();

    UNITY_BEGIN();    // IMPORTANT LINE!
    //showTest("to16bitColor", 0);
    //RUN_TEST(trivialTest);
    //RUN_TEST(test_led_builtin_pin_number);
    //RUN_TEST(test_to16bitColor);
    //showName("Matrix", 1);

    pinMode(LED_BUILTIN, OUTPUT);

    UNITY_END();
}

uint8_t i = 0;
uint8_t max_blinks = 5;

void loop() {
    if (i < max_blinks)
    {
        RUN_TEST(test_led_state_high);
        delay(500);
        RUN_TEST(test_led_state_low);
        delay(500);
        i++;
    }
    else if (i == max_blinks) {
      UNITY_END(); // stop unit testing
    }
}
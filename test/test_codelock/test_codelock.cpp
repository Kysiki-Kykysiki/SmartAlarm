#include <unity.h>
#include <CodeLock.h>

void setUp(void) {}
void tearDown(void) {}

// удобный помощник: "набрать" строку клавиш
static void typeKeys(CodeLock& lock, const char* keys) {
    for (const char* p = keys; *p; ++p) lock.pressKey(*p);
}

//тест1 на отрытие сейфа при правильном пароле
void test_correct_code_unlocks(void){
    CodeLock lock("1234");
    typeKeys(lock, "1234#");
    TEST_ASSERT_TRUE(lock.isUnlocked());
    TEST_ASSERT_EQUAL_INT(0, lock.getFailedAttempts());
}

//тест2 реакция на ввод неправильного пароля(сейф не открылся)
void test_wrong_code_does_not_unlock(void){
    CodeLock lock("1234");
    typeKeys(lock, "0000#");
    TEST_ASSERT_FALSE(lock.isUnlocked());
    TEST_ASSERT_EQUAL_INT(1, lock.getFailedAttempts());

}
//тест3 проверка на очистку неверного ввода
void test_star_clears_entry(void){
    CodeLock lock("1234");
    typeKeys(lock, "12");
    typeKeys(lock, "*");
    typeKeys(lock, "1234#");
    TEST_ASSERT_TRUE(lock.isUnlocked());
}

//тест4 проверка превышения лимитов ошибки
void test_lockout_after_max_attempts(void){
    CodeLock lock("1234", 3);
    typeKeys(lock, "111#");
    typeKeys(lock, "11211#");
    TEST_ASSERT_FALSE(lock.isLockedOut());
    typeKeys(lock, "11211#");
    TEST_ASSERT_TRUE(lock.isLockedOut());
    TEST_ASSERT_EQUAL_INT(3,lock.getFailedAttempts());
}

//тест5 слишком длинный ввод
void test_overflow_is_safe(void){
    CodeLock lock("1234");
    typeKeys(lock, "11782718378127381273817231#");
    TEST_ASSERT_FALSE(lock.isUnlocked());
    TEST_ASSERT_FALSE(lock.isLockedOut() && lock.getFailedAttempts() > 1);
}


int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_correct_code_unlocks);
    RUN_TEST(test_wrong_code_does_not_unlock);
    RUN_TEST(test_star_clears_entry);
    RUN_TEST(test_lockout_after_max_attempts);
    RUN_TEST(test_overflow_is_safe);
    return UNITY_END();
}

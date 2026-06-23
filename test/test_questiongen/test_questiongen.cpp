#include <QuestionGen.h>
#include <unity.h>

void setUp(void){} // -> первичная настройка(параметры, действия, которые нужно сделать вначале). Аналог - setup() в arduino
void tearDown(void){}

void test_answer_mathes_operator(void){
    QuestionGen gen(2,10);
    for (int i = 0; i < 200; i++){
        Question q = gen.next();
        int expected = 0;
        switch (q.op)
        {
        case '+': expected = q.a + q.b; break;
        case '-': expected = q.a - q.b; break;
        case '*': expected = q.a * q.b; break;
        
        default:
            TEST_FAIL_MESSAGE("Недопустимая операция!");
            break;
        }
        TEST_ASSERT_EQUAL_INT(expected, q.answer);
    }
}

void test_operands_in_range(void){
    QuestionGen gen(2,10);
    for (int i = 0; i < 200; i++){
        Question q = gen.next();
        TEST_ASSERT_TRUE(q.a >= 2 && q.a <= 10);
        TEST_ASSERT_TRUE(q.b >= 2 && q.b <= 10);
    }
}

void test_subtraction_non_negative(void){
    QuestionGen gen(2,10);
    for (int i = 0; i < 200; i++){
        Question q = gen.next();
        if(q.op == '-'){
            TEST_ASSERT_TRUE_MESSAGE(q.answer >= 0, "Отрицание");
        }
    }
}

void test_operator_is_valid(void){
    QuestionGen gen(2,10);
    for (int i = 0; i < 200; i++){
        Question q = gen.next();
        bool ok = (q.op == '+' || q.op == '-' || q.op == '*');
        TEST_ASSERT_TRUE_MESSAGE(ok, "Неизвестная операция");
    }
}

void test_single_value_range(void){
    QuestionGen gen(5,5);
    for(int i = 0; i < 200; i++){
        Question q = gen.next();
        TEST_ASSERT_EQUAL_INT(5, q.a);
        TEST_ASSERT_EQUAL_INT(5, q.b);
    }
}

int main(int argc, char **argv){
    UNITY_BEGIN();
    RUN_TEST(test_answer_mathes_operator);
    RUN_TEST(test_operands_in_range);
    RUN_TEST(test_subtraction_non_negative);
    RUN_TEST(test_operator_is_valid);
    RUN_TEST(test_single_value_range);
    return UNITY_END();

}
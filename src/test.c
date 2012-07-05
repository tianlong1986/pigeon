#include "test.h"

void test_print()
{
	g_message("hi,this is %s-%s-%d",__FILE__,__func__,__LINE__);
}

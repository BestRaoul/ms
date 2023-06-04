//
// Created by jack on 6/4/23.
//

#include "ms.h"

void free_lexeme_node(void *node)
{
	t_dict_int_str_member_free(node);
	//free(node);
}

 /*
    if ((*root) == NULL)
    {
        Tree *p = (Tree *)malloc(sizeof(Tree));
        p->left = NULL;
        p->right = NULL;
        p->val = num;
        *root = p;
    }
    else
    {
        if ((*root)->val >= num)
        {
            Tree_insert(&((*root)->left), num);
        }
        else
        {
            Tree_insert(&((*root)->right), num);
        }
    }
*/
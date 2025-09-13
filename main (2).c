/* COP 3502C Assignment 5
This program is written by: Zainab Syed */

#include <stdlib.h>
#include <stdio.h>

typedef struct tree_node {
    int data;
    char name[26];
    int depth;
    struct tree_node *left;
    struct tree_node *right;
} tree_node;

tree_node* create_node(int val, char name[]) {
    // Allocate space for the node, set the fields.
    tree_node* temp;
    temp = (tree_node*)malloc(sizeof(tree_node));
    temp->data = val;
    temp->depth = 0;
    strcpy(temp->name, name);
    temp->left = NULL;
    temp->right = NULL;
    return temp; // Return a pointer to the created node.
}

tree_node* insert(tree_node *root, tree_node *element) {
    // Inserting into an empty tree.
    if (root == NULL) {
        return element;
    }
    else {       
        // element should be inserted to the right.
        if (strcmp(element->name, root->name) > 0) {
            // There is a right subtree to insert the node.
            if (root->right != NULL)
                root->right = insert(root->right, element);
            // Place the node directly to the right of root.
            else
                root->right = element;
        }
        // element should be inserted to the left.
        else {
            // There is a left subtree to insert the node.
            if (root->left != NULL)
                root->left = insert(root->left, element);
            // Place the node directly to the left of root.
            else
                root->left = element;
        }
        // Return the root pointer of the updated tree.
        return root;
    }
}

tree_node* findNode(tree_node *current_ptr, char name[]) {
    // Check if there are nodes in the tree.
    if (current_ptr != NULL) {
        // Found the value at the root.
        if (strcmp(name, current_ptr->name) == 0) {
            return current_ptr;
        }
        // search the left
        if (strcmp(name, current_ptr->name) < 0) {
            return findNode(current_ptr->left, name);
        }
        // search the right
        else {
            return findNode(current_ptr->right, name);
        }
    }
    else
        return NULL; // No node found.
}

int findDepth(tree_node* current, char name[]) {
    if (current != NULL) {
        // Found the value at the root.
        if (strcmp(name, current->name) == 0) {
            return 0;
        }
        // search the left
        if (strcmp(name, current->name) < 0) {
            return 1 + findDepth(current->left, name);
        }
        // search the right
        else {
            return 1 + findDepth(current->right, name);
        }
    }  
    return 0;
}

int calc_b(tree_node* root, char* name) {
    if (root == NULL) {
        // printf("Reached NULL node\n");
        return 0;
    }
    else {
        // printf("visiting node: %s \n", root->name);
        int count = 0;
        if (strcmp(root->name, name) <= 0) {
            count+= calc_b(root->left, name);
            count+= root->data;
            count+= calc_b(root->right, name);
        }
        else {
            count+= calc_b(root->left, name);
        }
        return count;
    }
}

int total_fines(tree_node* root) {
    if(root == NULL) {
        return 0;
    }
    // if(current == NULL) {
    //     return 0;
    // }
    else if(numnodes(root) == 1) {
        return root->data;
    }
    // if(parent(root, current) == NULL) {
    //     return 0;
    // }
    else{
        int total = 0;
        // printf("accessing node: %s current total: %d", root->name, total);
        // total += total_fines(root, current->left);
        // total += current->data;
        // total += total_fines(root, current->right);
        total += total_fines(root->left);
        total += root->data;
        total += total_fines(root->right);
        return total;
    }
}

int numnodes(tree_node* root) {
    if (root == NULL) {
        return 0; 
        }
    // else if(root->left == NULL && root->right == NULL) {
    //     return 1;
    // }
    return 1 + numnodes(root->left) + numnodes(root->right);
}

//===============================================================
tree_node* maxVal(tree_node *root) {

  // Root stores the maximal value.
  if (root->right == NULL)
    return root;

  // The right subtree of the root stores the maximal value.
  else
    return maxVal(root->right);
}

tree_node* parent(tree_node *root, tree_node *node) {

  // Take care of NULL cases.
  if (root == NULL || root == node)
    return NULL;

  // The root is the direct parent of node.
  if (root->left == node || root->right == node)
    return root;

  // Look for node's parent in the left side of the tree.
  if (strcmp(node->name, root->name) < 0)
    return parent(root->left, node);

  // Look for node's parent in the right side of the tree.
  else {
    return parent(root->right, node); }

  return NULL; // Catch any other extraneous cases.

}

int isLeaf(struct tree_node *node) {
    return (node->left == NULL && node->right == NULL);
}

// Returns 1 iff node has a left child and no right child.
int hasOnlyLeftChild(tree_node *node) {
  return (node->left!= NULL && node->right == NULL);
}

// Returns 1 iff node has a right child and no left child.
int hasOnlyRightChild(tree_node *node) {
  return (node->left== NULL && node->right != NULL);
}

tree_node* delete1(tree_node* root, char name[], int fine) {

    tree_node *delnode, *new_del_node, *save_node;
    tree_node *par;
    int save_val;
    char save_name[26];

    delnode = findNode(root, name); // Get a pointer to the node to delete.
    if (delnode == NULL) {
        //printf("%s not found\n", name);
        return root;
    }
    // printf("node to delete: %s\n", delnode->name);

    par = parent(root, delnode); // Get the parent of this node.
    //if(par != NULL) {
        // printf("parent node: %s\n", par->name);
    //}

    // Take care of the case where the node to delete is a leaf node.
    if (isLeaf(delnode)) {// case 1

        // Deleting the only node in the tree.
        if (par == NULL) {
            if (((delnode->data)-fine) <= 0) {
                //printf("%s removed\n",root->name);
                free(root);
                root = NULL;
                return root;
            }
            else {
                delnode->data = delnode->data - fine;
                printf("%s %d %d\n", delnode->name, delnode->data, delnode->depth);
                return root;
            }
        }

        // Deletes the node if it's a left child.
        if (strcmp(name, par->name) < 0) {
            if(((delnode->data)-fine) <= 0) {
                // printf("%s removed\n", par->left->name);
                free(delnode); // Free the memory for the node.
                par->left = NULL;
                return NULL;
            }
            else {
                delnode->data = delnode->data - fine;
                printf("%s %d %d\n", delnode->name, delnode->data, delnode->depth);
            }
        }

        // Deletes the node if it's a right child.
        else {
            if(((delnode->data)-fine) <= 0) {
                // printf("%s removed\n", par->right->name);
                free(delnode); // Free the memory for the node.
                par->right = NULL;
                return NULL;
            }
            else {
                delnode->data = delnode->data - fine;
                printf("%s %d %d\n", delnode->name, delnode->data, delnode->depth);
            }
        }

        return root; // Return the root of the new tree.
    }

    // Take care of the case where the node to be deleted only has a left
    // child.
    if (hasOnlyLeftChild(delnode)) {

        // Deleting the root node of the tree.
        if (par == NULL) {
            if((delnode->data - fine) <= 0) {
                save_node = delnode->left;
                printf("%s removed\n", delnode->name);
                free(delnode); // Free the node to delete.
                // return save_node; // Return the new root node of the resulting tree.
                root = save_node;
                root->depth = 0;
                return root;
                //return save_node;
            }
            else {
                delnode->data = delnode->data - fine;
                printf("%s %d %d\n", delnode->name, delnode->data, delnode->depth);
                return root;
            }
        }

        // Deletes the node if it's a left child.
        if (strcmp(name, par->name) < 0) {
            if (((delnode->data) - fine) <= 0) {
                // printf("%s removed\n", delnode->name);
                save_node = par->left; // Save the node to delete.
                par->left = par->left->left; // Re-adjust the parent pointer.
                free(delnode); // Free the memory for the deleted node.
                return NULL;
            }
            else {
                delnode->data = delnode->data - fine;
                printf("%s %d %d\n", delnode->name, delnode->data, delnode->depth);
            }
        }

        // Deletes the node if it's a right child.
        else {
            if (((delnode->data) - fine) <= 0) {
                // printf("%s removed\n", delnode->name);
                save_node = par->right; // Save the node to delete.
                par->right = par->right->left; // Re-adjust the parent pointer.
                free(delnode); // Free the memory for the deleted node.
                return NULL;
            }
            else {
                delnode->data = delnode->data - fine;
                printf("%s %d %d\n", delnode->name, delnode->data, delnode->depth);
            }
        }
        //return root; // Return the root of the tree after the deletion.
        return root;
    }

    // Takes care of the case where the deleted node only has a right child.
    if (hasOnlyRightChild(delnode)) {

        // Node to delete is the root node.
        if (par == NULL) {
            if((delnode->data - fine) <= 0) {
                printf("%s removed\n", delnode->name);
                save_node = delnode->right;
                free(delnode); // Free the node to delete.
                // return save_node; // Return the new root node of the resulting tree.
                root = save_node;
                return root;
            }
            else {
                delnode->data = delnode->data - fine;
                printf("%s %d %d\n", delnode->name, delnode->data, delnode->depth);
                // return delnode;
                return root;
            }
        }

        // Delete's the node if it is a left child.
        if (strcmp(name, par->name) < 0) {
            if (((par->left->data) - fine) <= 0) {
                // printf("%s removed\n", delnode->name);
                save_node = par->left; // Save the node to delete.
                par->left = par->left->right; // Re-adjust the parent pointer.
                free(save_node); // Free the memory for the deleted node.
                return NULL;
            }
            else {
                delnode->data = delnode->data - fine;
                printf("%s %d %d\n", delnode->name, delnode->data, delnode->depth);
                return root;
            }
        }

        // Delete's the node if it is a right child.
        else {
            if (((par->right->data) - fine) <= 0) {
                // printf("%s removed\n", delnode->name);
                save_node = par->right; // Save the node to delete.
                par->right = par->right->right; // Re-adjust the parent pointer.
                free(save_node); // Free the memory for the deleted node.
                return NULL;
            }
            else {
                delnode->data = delnode->data - fine;
                printf("%s %d %d\n", delnode->name, delnode->data, delnode->depth);
                return root;
            }
        }
        return root;
    }

    // the node has 2 children
    if((delnode->data)-fine <= 0) {
        // gets the max val from the left subtree to replace the node
        new_del_node = maxVal(delnode->left);

        strcpy(save_name, new_del_node->name);
        save_val = new_del_node->data;
        // printf("%s %d was saved for replacement\n", save_name, save_val);

        delete1(root, save_name, save_val);

        printf("%s removed\n", delnode->name);
        delnode->data = save_val;
        strcpy(delnode->name, save_name);
        // printf("%s replaces the node removed\n", delnode->name);
    }
    else { // if the deductions isn't greater than or equal to the fine
        delnode->data = delnode->data - fine;
        printf("%s %d %d\n", delnode->name, delnode->data, delnode->depth);
    }

    return root;
}


int tree_height(tree_node* root) {
    if (root == NULL) {
        return -1;
    }
    if(isLeaf(root)) {
        return 0;
    }
    else {
        int left_tree = tree_height(root->left);
        int right_tree = tree_height(root->right);

        if(left_tree > right_tree) {
            return 1 + left_tree;
        }
        else {
            return 1 + right_tree;
        } 
    }
    return 0;
}

void postorder_free(tree_node* root) {
    if (root != NULL) {
        postorder_free(root->left);
        postorder_free(root->right);
        free(root);
    }
}

int main() {
    int num_commands;
    tree_node* root = NULL;
    scanf("%d", &num_commands);
    
    char command[25];
    int total_nodes = 0;
    int total_fine = 0;
    for(int i = 0; i < num_commands; i++) {
        scanf("%s", command);
        if (strcmp(command, "add") == 0) {
            char name[26];
            int fine;
            scanf("%s %d", name, &fine);

            tree_node* temp = findNode(root, name);
            // if this person isn't already in the tree
            if(temp == NULL) {
                temp = create_node(fine, name);
                root = insert(root, temp);
                //total_nodes++;
                //total_fine += temp->data;
            }
            else {
                temp->data += fine;
                //total_fine += temp->data;
            }
            temp->depth = findDepth(root, name);
            printf("%s %d %d\n", temp->name, temp->data, temp->depth);
        }

        if (strcmp(command, "deduct")== 0) {
            char name[26];
            int fine;
            scanf("%s %d", name, &fine);
            
            // 
            tree_node* temp = findNode(root, name);
            if (temp == NULL) {
                printf("%s not found\n", name);
            }
            else if (parent(root, temp) == NULL) {
                root = delete1(root, name, fine);
                if(root == NULL) {
                    printf("%s removed\n", name);
                }
                //total_nodes--;
                //total_fine -= fine;
            }
            else {
                temp = delete1(root, name, fine);
                //total_fine-=fine;
                if (temp == NULL) {
                    printf("%s removed\n", name);
                    //total_nodes--;
                }
            }
        }

        if (strcmp(command, "search") == 0) {
            char name[26];            
            scanf("%s", name);
            tree_node* temp = findNode(root, name);
            if (temp != NULL) {
                temp->depth = findDepth(root, name);
                printf("%s %d %d\n", temp->name, temp->data, temp->depth);
            }
            else {
                printf("%s not found\n", name);
            }
        }
        // gets total finds and the num of nodes, then calculates the average
        if (strcmp(command, "average") == 0) {
            int total = total_fines(root);
            int num_nodes = numnodes(root);

            double avg = (total * 1.0) / num_nodes;
            //double avg = (total_fine * 1.0) / total_nodes;

            printf("%.2f\n", avg);
        }
        if (strcmp(command, "height_balance") == 0) {
            // determines heights of the left and right sub-trees
            // if(root == NULL) {
            //     printf("left height = -1 right height = -1 balanced\n");
            // }
            if (root!= NULL) {
                int left = tree_height(root->left);
                int right = tree_height(root->right);
                
                if(right == left) {
                    printf("left height = %d right height = %d balanced\n", left, right);
                }
                else {
                    printf("left height = %d right height = %d not balanced\n", left, right);
                }
            }
            else {
                printf("NO NODES\n");
            }
        }
        // Calculates total fines for names that come alphabetically before the input
        if (strcmp(command, "calc_below") == 0) {
            char name[26];
            scanf("%s", name);
            int total_below = calc_b(root, name);
            //printf("total below: %d\n", total_below);
            printf("%d\n", total_below);
        }
    }
    postorder_free(root);
    return 0;
}
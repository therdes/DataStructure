using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AVLTree
{
    class AVLTree
    {
        private AVLNode root;
        private int size;

        public const int LEFTHIGH = 1;
        public const int EQUALHIGH = 0;
        public const int RIGHTHIGH = -1;

        private int ErrorCode;
        public const int NORMAL = 0;
        public const int NONEXIST = 1;
        public const int HAVEEXIST = 2;

        public AVLTree()
        {
            root = null;
            size = 0;
        }

        public void Insert(int data)
        {
            bool isTaller = false;
            root = Insert(data, root, ref isTaller);
            size++;
        }
        private AVLNode Insert(int data, AVLNode root, ref bool isTaller)
        {
            if (root == null)
            {
                isTaller = true;
                return new AVLNode(data);
            }
            else
            {
                if (data == root.Data())
                {
                    isTaller = false;
                    return root;
                }
                else if (data < root.Data())
                {
                    root.leftChild = Insert(data, root.leftChild, ref isTaller);
                    if (isTaller)
                    {
                        switch (root.balancedFactor)
                        {
                            case LEFTHIGH:
                                root = LeftBalance(root);
                                isTaller = false;
                                break;

                            case EQUALHIGH:
                                root.balancedFactor = LEFTHIGH;
                                isTaller = true;
                                break;

                            case RIGHTHIGH:
                                root.balancedFactor = EQUALHIGH;
                                isTaller = false;
                                break;
                        }
                    }
                }
                else
                {
                    root.rightChild = Insert(data, root.rightChild, ref isTaller);
                    if (isTaller)
                    {
                        switch (root.balancedFactor)
                        {
                            case LEFTHIGH:
                                root.balancedFactor = EQUALHIGH;
                                isTaller = false;
                                break;

                            case EQUALHIGH:
                                root.balancedFactor = RIGHTHIGH;
                                isTaller = true;
                                break;

                            case RIGHTHIGH:
                                root = RightBalance(root);
                                isTaller = false;
                                break;
                        }
                    }
                }
                return root;
            }
        }

        private AVLNode RightRotate(AVLNode root)
        {
            AVLNode LChild = root.leftChild;
            root.leftChild = LChild.rightChild;
            LChild.rightChild = root;
            return LChild;
        }
        private AVLNode LeftRotate(AVLNode root)
        {
            AVLNode RChild = root.rightChild;
            root.rightChild = RChild.leftChild;
            RChild.leftChild = root;
            return RChild;
        }

        private AVLNode LeftBalance(AVLNode root)
        {
            AVLNode LChild = root.leftChild;
            AVLNode Lrchild;

            switch (LChild.balancedFactor)
            {
                case LEFTHIGH:
                    root.balancedFactor = EQUALHIGH;
                    LChild.balancedFactor = EQUALHIGH;
                    root = RightRotate(root);
                    break;

                case RIGHTHIGH:
                    Lrchild = LChild.rightChild;
                    switch (Lrchild.balancedFactor)
                    {
                        case LEFTHIGH:
                            root.balancedFactor = RIGHTHIGH;
                            LChild.balancedFactor = EQUALHIGH;
                            break;
                        case EQUALHIGH:
                            root.balancedFactor = EQUALHIGH;
                            LChild.balancedFactor = EQUALHIGH;
                            break;
                        case RIGHTHIGH:
                            root.balancedFactor = EQUALHIGH;
                            LChild.balancedFactor = LEFTHIGH;
                            break;
                    }
                    Lrchild.balancedFactor = EQUALHIGH;
                    root.leftChild = LeftRotate(LChild);
                    root = RightRotate(root);
                    break;
            }
            return root;
        }
        private AVLNode RightBalance(AVLNode root)
        {
            AVLNode Rchild = root.rightChild;
            AVLNode Rlchild;

            switch (Rchild.balancedFactor)
            {
                case RIGHTHIGH:
                    root.balancedFactor = EQUALHIGH;
                    Rchild.balancedFactor = EQUALHIGH;
                    root = LeftRotate(root);
                    break;

                case LEFTHIGH:
                    Rlchild = Rchild.leftChild;
                    switch (Rlchild.balancedFactor)
                    {
                        case RIGHTHIGH:
                            root.balancedFactor = LEFTHIGH;
                            Rchild.balancedFactor = EQUALHIGH;
                            break;
                        case EQUALHIGH:
                            root.balancedFactor = EQUALHIGH;
                            Rchild.balancedFactor = EQUALHIGH;
                            break;
                        case LEFTHIGH:
                            root.balancedFactor = EQUALHIGH;
                            Rchild.balancedFactor = RIGHTHIGH;
                            break;
                    }
                    Rlchild.balancedFactor = EQUALHIGH;
                    root.rightChild = RightRotate(Rchild);
                    root = LeftRotate(root);
                    break;
            }
            return root;
        }

        private AVLNode ParentofNodeFromLeft(AVLNode root, AVLNode target)
        {
            if (root == null)
                return null;
            else if (root.leftChild == target)
                return root;
            else
                return ParentofNodeFromLeft(root.leftChild, target);

        }
        private AVLNode ParentofNodeFromRight(AVLNode root, AVLNode target)
        {
            if (root == null)
                return null;
            else if (root.rightChild == target)
                return root;
            else
                return ParentofNodeFromRight(root.rightChild, target);
        }
        private AVLNode Min(AVLNode root)
        {
            return ParentofNodeFromLeft(root, null);
        }
        private AVLNode Max(AVLNode root)
        {
            return ParentofNodeFromRight(root, null);
        }

        public int Remove(int data)
        {
            bool isShorter = false;
            ErrorCode = NORMAL;
            root = Remove(data, root, null, ref isShorter);
            if (!isBalancedTree(this.root))
                return -1;
            if (ErrorCode == NORMAL)
                size--;
            return ErrorCode;
        }
        private AVLNode Remove(int data, AVLNode root, AVLNode DPC, ref bool isShorter)
        {
            if (root == null)
            {
                ErrorCode = NONEXIST;
                isShorter = false;
                return root;
            }

            else if (data < root.Data())
            {
                root.leftChild = Remove(data, root.leftChild, DPC, ref isShorter);
                if (isShorter)
                {
                    switch (root.balancedFactor)
                    {
                        case LEFTHIGH:
                            root.balancedFactor = EQUALHIGH;
                            isShorter = true;
                            break;

                        case EQUALHIGH:
                            root.balancedFactor = RIGHTHIGH;
                            isShorter = false;
                            break;

                        case RIGHTHIGH:
                            switch (root.rightChild.balancedFactor)
                            {
                                case LEFTHIGH:
                                    root.rightChild = RightRotate(root.rightChild);
                                    root.balancedFactor = EQUALHIGH;
                                    root.rightChild.balancedFactor = EQUALHIGH;
                                    isShorter = true;
                                    break;
                                case RIGHTHIGH:
                                    root.balancedFactor = EQUALHIGH;
                                    root.rightChild.balancedFactor = EQUALHIGH;
                                    isShorter = true;
                                    break;
                                case EQUALHIGH:
                                    root.balancedFactor = RIGHTHIGH;
                                    root.rightChild.balancedFactor = LEFTHIGH;
                                    isShorter = false;
                                    break;
                            }
                            root = LeftRotate(root);
                            break;
                    }
                }
                if (ErrorCode != NORMAL)
                    return root;
            }
            else if (data > root.Data())
            {
                root.rightChild = Remove(data, root.rightChild, DPC, ref isShorter);
                if (isShorter)
                {
                    switch (root.balancedFactor)
                    {
                        case LEFTHIGH:
                            switch (root.leftChild.balancedFactor)
                            {
                                case RIGHTHIGH:
                                    root.leftChild = LeftRotate(root.leftChild);
                                    root.balancedFactor = EQUALHIGH;
                                    root.leftChild.balancedFactor = EQUALHIGH;
                                    isShorter = true;
                                    break;
                                case LEFTHIGH:
                                    root.balancedFactor = EQUALHIGH;
                                    root.leftChild.balancedFactor = EQUALHIGH;
                                    isShorter = true;
                                    break;
                                case EQUALHIGH:
                                    root.balancedFactor = LEFTHIGH;
                                    root.leftChild.balancedFactor = RIGHTHIGH;
                                    isShorter = false;
                                    break;
                            }
                            root = RightRotate(root);
                            break;

                        case EQUALHIGH:
                            root.balancedFactor = LEFTHIGH;
                            isShorter = false;
                            break;

                        case RIGHTHIGH:
                            root.balancedFactor = EQUALHIGH;
                            isShorter = true;
                            break;
                    }
                }
                if (ErrorCode != NORMAL)
                    return root;
            }

            else if (root.leftChild == null && root.rightChild == null)
            {
                root = null;
                isShorter = true;
            }
            else
            {
                if (root.leftChild != null && root.rightChild == null)
                {
                    root = RightRotate(root);
                    root.rightChild = Remove(data, root.rightChild, DPC, ref isShorter);
                }
                else if (root.leftChild == null && root.rightChild != null)
                {
                    root = LeftRotate(root);
                    root.leftChild = Remove(data, root.leftChild, DPC, ref isShorter);
                }

                else
                {
                    DPC = Max(root.leftChild);
                    root = RightRotate(root);
                    root.rightChild = Remove(data, root.rightChild, DPC, ref isShorter);

                    if (DPC != null && root.rightChild == DPC)
                    {
                        switch (root.balancedFactor)
                        {
                            case LEFTHIGH:
                                root.balancedFactor = EQUALHIGH;
                                root.leftChild.balancedFactor = EQUALHIGH;
                                root = RightRotate(root);
                                break;
                            case EQUALHIGH:
                                root.balancedFactor = LEFTHIGH;
                                break;
                            case RIGHTHIGH:
                                root.balancedFactor = EQUALHIGH;
                                break;
                        }
                        root = LeftRotate(root);
                    }
                }
            }
            return root;
        }

        public int Height()
        {
            return Height(root);
        }
        private int Height(AVLNode root)
        {
            if (root == null)
                return 0;

            int leftH = Height(root.leftChild);
            int rightH = Height(root.rightChild);
            int max = (leftH > rightH) ? leftH : rightH;

            return max + 1;
        }

        private bool isBalancedTree(AVLNode root)
        {
            if (root == null)
                return true;

            bool left = isBalancedTree(root.leftChild);
            bool right = isBalancedTree(root.rightChild);

            bool thisSubTree = true;
            int temp = Height(root.leftChild) - Height(root.rightChild);
            if (temp < RIGHTHIGH || temp > LEFTHIGH)
                thisSubTree = false;

            if (left && right && thisSubTree)
                return true;
            else
                return false;
        }
    }
}

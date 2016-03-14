using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AVLTree
{
    class AVLNode
    {
        private int data;

        public int balancedFactor;

        public AVLNode leftChild;
        public AVLNode rightChild;

        public AVLNode(int data)
        {
            this.data = data;
        }

        public int Data()
        {
            return data;
        }
    }
}

    package DataStructures;

    // Basic node stored in a linked list -- cursor version
    // Note that this class is not accessible outside
    // of package DataStructures

    class CursorNode
    {
            // Constructors
        CursorNode( Object theElement )
        {
            this( theElement, 0 );
        }

        CursorNode( Object theElement, int n )
        {
            element = theElement;
            next    = n;
        }

            // Friendly data; accessible by other package routines
        Object   element;
        int      next;
    }

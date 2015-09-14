    package DataStructures;

    // StackAr class
    //
    // CONSTRUCTION: with or without a capacity; default is 10
    //
    // ******************PUBLIC OPERATIONS*********************
    // void push( x )         --> Insert x
    // void pop( )            --> Remove most recently inserted item
    // Object top( )          --> Return most recently inserted item
    // Object topAndPop( )    --> Return and remove most recently inserted item
    // boolean isEmpty( )     --> Return true if empty; else false
    // boolean isFull( )      --> Return true if full; else false
    // void makeEmpty( )      --> Remove all items
    // ******************ERRORS********************************
    // Overflow and Underflow thrown as needed

    /**
     * Array-based implementation of the stack.
     * @author Mark Allen Weiss
     */
    public class StackAr
    {
        /**
         * Construct the stack.
         */
        public StackAr( )
        {
            this( DEFAULT_CAPACITY );
        }

        /**
         * Construct the stack.
         * @param capacity the capacity.
         */
        public StackAr( int capacity )
        {
            theArray = new Object[ capacity ];
            topOfStack = -1;
        }

        /**
         * Test if the stack is logically empty.
         * @return true if empty, false otherwise.
         */
        public boolean isEmpty( )
        {
            return topOfStack == -1;
        }

        /**
         * Test if the stack is logically full.
         * @return true if full, false otherwise.
         */
        public boolean isFull( )
        {
            return topOfStack == theArray.length - 1;
        }

        /**
         * Make the stack logically empty.
         */
        public void makeEmpty( )
        {
            topOfStack = -1;
        }

        /**
         * Get the most recently inserted item in the stack.
         * Does not alter the stack.
         * @return the most recently inserted item in the stack, or null, if empty.
         */
        public Object top( )
        {
            if( isEmpty( ) )
                return null;
            return theArray[ topOfStack ];
        }

        /**
         * Remove the most recently inserted item from the stack.
         * @exception Underflow if stack is already empty.
         */
        public void pop( ) throws Underflow
        {
            if( isEmpty( ) )
                throw new Underflow( );
            theArray[ topOfStack-- ] = null;
        }

        /**
         * Insert a new item into the stack, if not already full.
         * @param x the item to insert.
         * @exception Overflow if stack is already full.
         */
        public void push( Object x ) throws Overflow
        {
            if( isFull( ) )
                throw new Overflow( );
            theArray[ ++topOfStack ] = x;
        }

        /**
         * Return and remove most recently inserted item from the stack.
         * @return most recently inserted item, or null, if stack is empty.
         */
        public Object topAndPop( )
        {
            if( isEmpty( ) )
                return null;
            Object topItem = top( );
            theArray[ topOfStack-- ] = null;
            return topItem;
        }

        private Object [ ] theArray;
        private int        topOfStack;

        static final int DEFAULT_CAPACITY = 10;

        public static void main( String [ ] args )
        {
            StackAr s = new StackAr( 12 );

            try
            {
                for( int i = 0; i < 10; i++ )
                    s.push( new MyInteger( i ) );
            }
            catch( Overflow e ) { System.out.println( "Unexpected overflow" ); }

            while( !s.isEmpty( ) )
                System.out.println( s.topAndPop( ) );
        }        
    }

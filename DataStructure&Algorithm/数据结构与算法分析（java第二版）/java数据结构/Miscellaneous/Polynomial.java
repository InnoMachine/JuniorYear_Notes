    import DataStructures.Overflow;
 
    /*
     * This code doesn't really do much, and abstraction is not built in.
     * Thus, I haven't bothered testing it exhaustively.
     */

    public class Polynomial
    {
        public static final int MAX_DEGREE = 100;

        public static int max( int a, int b )
        {
            return a > b ? a : b;
        }

        public Polynomial( )
        {
           zeroPolynomial( );
        }

        public void zeroPolynomial( )
        {
            for( int i = 0; i <= MAX_DEGREE; i++ )
                coeffArray[ i ] = 0;
            highPower = 0;
        }

        public Polynomial add( Polynomial rhs )
        {
            Polynomial sum = new Polynomial( );

            sum.highPower = max( highPower, rhs.highPower );
            for( int i = sum.highPower; i >= 0; i-- )
                sum.coeffArray[ i ] = coeffArray[ i ] + rhs.coeffArray[ i ];
            return sum;
        }

        public Polynomial multiply( Polynomial rhs ) throws Overflow
        {
            Polynomial product = new Polynomial( );

            product.highPower = highPower + rhs.highPower;
            if( product.highPower > MAX_DEGREE )
                throw new Overflow( );
            for( int i = 0; i <= highPower; i++ )
                for( int j = 0; j <= rhs.highPower; j++ )
                    product.coeffArray[ i + j ] +=
                            coeffArray[ i ] * rhs.coeffArray[ j ];
            return product;
        }

        public void print( )
        {
            for( int i = highPower; i > 0; i-- )
                 System.out.print( coeffArray[ i ] + "x^" + i + " + " );
            System.out.println( coeffArray[ 0 ] );
        }
  
        private int coeffArray[ ] = new int [ MAX_DEGREE + 1 ];
        private int highPower = 0;


        public static void main( String [ ] args )
        {
            Polynomial p = new Polynomial( );
            Polynomial q;

            p.highPower = 1; p.coeffArray[ 0 ] = 1; p.coeffArray[ 1 ] = 1;

            try
            {
                q = p.multiply( p );
                p = q.multiply( q );
            }
            catch( Overflow e ) { System.out.println( "Unexpected overflow" ); }
            q = p.add( p );
            q.print( );
        }
    }

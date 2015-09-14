public class Fig02_11
{
        public static boolean isEven( int n )
        {
            return n % 2 == 0;
        }

/* START: Fig02_11.txt*/
        public static long pow( long x, int n )
        {
/* 1*/      if( n == 0 )
/* 2*/          return 1;
/* 3*/      if( n == 1 )
/* 4*/          return x;
/* 5*/      if( isEven( n ) )
/* 6*/          return pow( x * x, n / 2 );
            else
/* 7*/          return pow( x * x, n / 2 ) * x;
        }
/* END */

        // Test program
        public static void main( String [ ] args )
        {
            System.out.println( "2^21 = " + pow( 2, 21 ) );
            System.out.println( "2^50 = " + pow( 2, 50 ) );
        }
    }

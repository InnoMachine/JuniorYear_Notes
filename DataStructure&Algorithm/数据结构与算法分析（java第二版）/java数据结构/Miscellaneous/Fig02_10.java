public class Fig02_10
{
/* START: Fig02_10.txt*/
        public static long gcd( long m, long n )
        {
/* 1*/      while( n != 0 )
            {
/* 2*/          long rem = m % n;
/* 3*/          m = n;
/* 4*/          n = rem;
            }
/* 5*/      return m;
        }
/* END */

        // Test program
        public static void main( String [ ] args )
        {
            System.out.println( "gcd( 45, 35 ) = " + gcd( 45, 35 ) );
            System.out.println( "gcd( 1989, 1590 ) = " + gcd( 1989, 1590 ) );
        }
    }

    public class Fig01_03
    {

/* START: Fig01_03.txt */
        public static int bad( int n )
        {
/* 1*/      if( n == 0 )
/* 2*/          return 0;
            else
/* 3*/          return bad( n / 3 + 1 ) + n - 1;
        }
/* END */

        public static void main( String [ ] args )
        {
            System.out.println( "Bad is infinite recursion" );
        }
    }

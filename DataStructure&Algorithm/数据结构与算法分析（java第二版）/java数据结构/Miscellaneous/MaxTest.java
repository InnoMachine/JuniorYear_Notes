    import java.io.*;
    import java.util.*;

    // Read two integers and output the maximum.

    public class MaxTest
    {
        public static void main( String [ ] args )
        {
/* 1*/      BufferedReader in = new BufferedReader( new
                                 InputStreamReader( System.in ) );
/* 2*/      String oneLine;
/* 3*/      StringTokenizer str;
/* 4*/      int x;
/* 5*/      int y;

/* 6*/      System.out.println( "Enter 2 ints on one line: " );
/* 7*/      try
            {
/* 8*/          oneLine = in.readLine( );
/* 9*/          str = new StringTokenizer( oneLine );
/*10*/          if( str.countTokens( ) != 2 )
/*11*/              throw new NumberFormatException( );
/*12*/          x = Integer.parseInt( str.nextToken( ) );
/*13*/          y = Integer.parseInt( str.nextToken( ) );
/*14*/          System.out.println( "Max: " + Math.max( x, y ) );
            }
/*15*/      catch( Exception e )
/*16*/        { System.err.println( "Error: need two ints" ); }
        }
    }

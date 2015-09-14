
    import java.io.*;

    public class DivideByTwo
    {
        public static void main( String [ ] args )
        {
/* 1*/      BufferedReader in = new BufferedReader( new
                             InputStreamReader( System.in ) );
/* 2*/      int x;
/* 3*/      String oneLine;

/* 4*/      System.out.println( "Enter an integer: " );
/* 5*/      try
/* 6*/      {
/* 7*/          oneLine = in.readLine( );
/* 8*/          x = Integer.parseInt( oneLine );
/* 9*/          System.out.println( "Half of x is " + ( x / 2 ) );
/*10*/      }
/*11*/      catch( Exception e )
/*12*/        { System.out.println( e ); }
        }
    }

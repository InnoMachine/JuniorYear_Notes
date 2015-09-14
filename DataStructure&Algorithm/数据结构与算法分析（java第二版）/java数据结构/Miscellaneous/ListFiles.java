
    import java.io.*;
    public class ListFiles
    {
        public static void main( String [ ] args )
        {
/* 1*/      if( args.length == 0 )
/* 2*/          System.out.println( "No files specified" );
/* 3*/      for( int i = 0; i < args.length; i++ )
/* 4*/          listFile( args[ i ] );
        }

        public static void listFile( String fileName )
        {
            FileReader theFile;
            BufferedReader fileIn = null;
            String oneLine;

/* 5*/      System.out.println( "FILE: " + fileName );
/* 6*/      try
            {
/* 7*/          theFile = new FileReader( fileName );
/* 8*/          fileIn  = new BufferedReader( theFile );
/* 9*/          while( ( oneLine = fileIn.readLine( ) ) != null )
/*10*/              System.out.println( oneLine );
            }
/*11*/      catch( Exception e )
/*12*/        { System.out.println( e ); }

            // Close the stream
/*13*/      try
            {
/*14*/          if( fileIn != null )
/*15*/              fileIn.close( );
            }
/*16*/      catch( IOException e ) { }
        }
    }


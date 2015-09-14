    import java.io.*;

    public class NumberLines
    {
        public static void main( String [ ] args )
        {
            PrintWriter   fileOut = null;
            BufferedReader fileIn = null;

            try
            {
                if( args.length == 1 )
                    fileOut = new PrintWriter( System.out );
                else if( args.length == 0 || args.length > 2 )
                    throw new Exception( "Usage: java NumberLines sourceFile destFile" );
                else if( args[ 0 ].equals( args[ 1 ] ) )
                    throw new Exception( "Cannot copy to self" );
                else
                    fileOut = new PrintWriter( new BufferedWriter(
                                         new FileWriter( args[ 1 ] ) ) );

                fileIn  = new BufferedReader( new FileReader( args[ 0 ] ) );

                String oneLine;
                int lineNum = 0;

                while( ( oneLine = fileIn.readLine( ) ) != null )
                {
                    fileOut.print( ++lineNum + "\t");
                    fileOut.println( oneLine );
                }
            }
            catch( Exception e )
              { System.out.println( e ); }

            try
            {
                if( fileIn != null )
                    fileIn.close( );
                if( fileOut != null )
                    fileOut.close( );
            }
            catch( IOException e )
              { }
        }
    }

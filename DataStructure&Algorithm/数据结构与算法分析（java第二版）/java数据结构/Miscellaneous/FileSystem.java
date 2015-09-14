    import java.io.*;

    public class FileSystem extends File
    {
            // Constructor
        public FileSystem( String name )
        {
            super( name );
        }

            // Output file name with indentation
        public void printName( int depth )
        {
            for( int i = 0; i < depth; i++ )
                System.out.print( "\t" );
            System.out.println( getName( ) );
        }

            // Public driver to list all files in directory
        public void listAll( )
        { 
            listAll( 0 );
        }
 
            // Recursive method to list all files in directory
        private void listAll( int depth )
        {
            printName( depth );

            if( isDirectory( ) )
            {
                String [ ] entries = list( );

                for( int i = 0; i < entries.length; i++ )
                {
                    FileSystem child = new FileSystem( getPath( )
                                 + separatorChar + entries[ i ] );
                    child.listAll( depth + 1 );
                }
            }
        }

            // Simple main to list all files in current directory
        public static void main( String [ ] args )
        {
            FileSystem f = new FileSystem( "." );
            f.listAll( );
        }
    }

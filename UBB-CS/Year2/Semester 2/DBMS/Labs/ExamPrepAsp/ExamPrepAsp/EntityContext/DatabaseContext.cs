using Microsoft.EntityFrameworkCore;

namespace ExamPrepAsp.EntityContext
{
    public class DatabaseContext : DbContext
    {
        public DatabaseContext()
        {

        }
        public DatabaseContext(DbContextOptions<DatabaseContext> options) : base(options) 
        {
            
        }

    }
}

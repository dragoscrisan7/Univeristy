using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Configuration;

namespace Exam
{
    public partial class Form1 : Form
    {
        SqlConnection conn;
        SqlDataAdapter daClass;
        SqlDataAdapter daSubClass;
        DataSet dset;
        BindingSource bsClass;
        BindingSource bsSubClass;

        SqlCommandBuilder cmdBuilder;

        string queryClass;
        string querySubClass;
        public Form1()
        {
            InitializeComponent();
            FillData();
        }
        string getConnectionString()
        {
            return "Server=DESKTOP-810AP8O\\LABONE;Database=SemesterProject;Integrated Security=true";
        }
        void FillData()
        {
            conn = new SqlConnection(getConnectionString());
            try
            {
                queryClass = "Select * from StudentMembers";
                querySubClass = "Select * from Task";

                daClass = new SqlDataAdapter(queryClass, conn);
                daSubClass = new SqlDataAdapter(querySubClass, conn);
                dset = new DataSet();
                daClass.Fill(dset, "StudentMembers");
                daSubClass.Fill(dset, "Task");

                cmdBuilder = new SqlCommandBuilder(daSubClass);

                dset.Relations.Add("ClassSubclass",
                    dset.Tables["StudentMembers"].Columns["ID"],
                    dset.Tables["Task"].Columns["SMID"]);

                bsClass = new BindingSource();
                bsClass.DataSource = dset.Tables["StudentMembers"];
                bsSubClass = new BindingSource(bsClass, "ClassSubclass");

                this.dataGridView1.DataSource = bsClass;
                this.dataGridView2.DataSource = bsSubClass;

                cmdBuilder.GetUpdateCommand();
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }


        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            daSubClass.Update(dset, "Task");
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}

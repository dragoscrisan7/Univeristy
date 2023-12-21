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

namespace Dbms_retry
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

        string QueryClass;
        string QuerySubclass;
        public Form1()
        {
            InitializeComponent();
            FillData();
        }
        void FillData()
        {
            string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
            try
            {
                conn = new SqlConnection(con);
                string queryClass = ConfigurationManager.AppSettings["select"];
                string querySubClass = ConfigurationManager.AppSettings["select_sub"];

                string ClassName = ConfigurationManager.AppSettings["TableName"];
                string SubCLassName = ConfigurationManager.AppSettings["TableName_sub"];
                ClassLabel.Text = ClassName;
                SubClassLabel.Text = SubCLassName;

                daClass = new SqlDataAdapter(queryClass, conn);
                daSubClass = new SqlDataAdapter(querySubClass, conn);
                dset = new DataSet();
                daClass.Fill(dset, ClassName);
                daSubClass.Fill(dset, SubCLassName);

                cmdBuilder = new SqlCommandBuilder(daSubClass);

                dset.Relations.Add("ClassSubclass",
                    dset.Tables[ClassName].Columns[ConfigurationManager.AppSettings["PrimaryKeyName"]],
                    dset.Tables[SubCLassName].Columns[ConfigurationManager.AppSettings["ForeignKeyName"]]);

                bsClass = new BindingSource();
                bsClass.DataSource = dset.Tables[ClassName];
                bsSubClass = new BindingSource(bsClass, "ClassSubclass");

                ClassDataGrid.DataSource = bsClass;
                SubClassDataGrid.DataSource = bsSubClass;

                cmdBuilder.GetUpdateCommand();
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void UpdateButton_Click(object sender, EventArgs e)
        {
            try
            {
                daSubClass.Update(dset, ConfigurationManager.AppSettings["TableName_sub"]);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void ClassDataGrid_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}

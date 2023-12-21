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
using System.Data.SqlClient;
using System.Linq.Expressions;
using System.Configuration;
using System.Collections.Specialized;
using System.Xml;
using System.IO.Ports;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        SqlDataAdapter da_class = new SqlDataAdapter();
        SqlDataAdapter da_sub_class = new SqlDataAdapter();
        DataSet ds = new DataSet();
        int cid = 0, scid = 0;

        public Form1()
        {
            InitializeComponent();
        }
        private void dataGridView1_RowHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            List<string> ColumnNames = new List<string>(ConfigurationManager.AppSettings["ColumnNames"].Split(','));
            cid = Convert.ToInt32(dataGridView1.CurrentRow.Cells[0].Value.ToString());
            int i = 1;
            foreach (string column in ColumnNames)
            {
                TextBox textBox = (TextBox)panel1.Controls[column];
                textBox.Text = dataGridView1.CurrentRow.Cells[i].Value.ToString();
                i++;
            }
        }
        private void Connect_Button_Click(object sender, EventArgs e)
        {
            string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
            try
            {
                SqlConnection cs = new SqlConnection(con);
                string select = ConfigurationManager.AppSettings["select"];
                string table_name = ConfigurationManager.AppSettings["TableName"];
                da_class.SelectCommand = new SqlCommand(select, cs);
                ds.Clear();
                da_class.Fill(ds, table_name);

                string select_sub = ConfigurationManager.AppSettings["select_sub"];
                string sub_table_name = ConfigurationManager.AppSettings["TableName_sub"];
                da_sub_class.SelectCommand = new SqlCommand(select_sub, cs);
                da_sub_class.Fill(ds, sub_table_name);

                string fkn = ConfigurationManager.AppSettings["ForeignKeyName"];
                ds.Relations.Add("Class_Subclass",
                    ds.Tables[table_name].Columns["ID"],
                    ds.Tables[sub_table_name].Columns[fkn]);

                dataGridView1.DataSource = ds.Tables[table_name];
                dataGridView2.DataSource = dataGridView1.DataSource;
                dataGridView2.DataMember = "Class_Subclass";
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
        }

        private void Insert_Button_Click(object sender, EventArgs e)
        {
            string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
            try
            {
                SqlConnection cs = new SqlConnection(con);
                string table_name = ConfigurationManager.AppSettings["TableName"];
                string ColumnNames = ConfigurationManager.AppSettings["ColumnNames"];

                string ColumnNamesInsertParameters = ConfigurationManager.AppSettings["ColumnNamesInsertParameters"];
                List<string> ColumnNamesList = new List<string>(ConfigurationManager.AppSettings["ColumnNames"].Split(','));
                SqlCommand cmd = new SqlCommand("INSERT INTO " + table_name + "(" + ColumnNames + ") Values (" + ColumnNamesInsertParameters + ")", cs);
                foreach (string column in ColumnNamesList)
                {
                    TextBox textBox = (TextBox)panel1.Controls[column];
                    cmd.Parameters.AddWithValue("@" + column, textBox.Text);
                }
                string sub_table_name = ConfigurationManager.AppSettings["TableName_sub"];
                cs.Open();
                cmd.ExecuteNonQuery();
                ds.Clear();
                da_class.Fill(ds, table_name);
                da_sub_class.Fill(ds, sub_table_name);
                MessageBox.Show("Added succesfully!");
                cs.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void Delete_Button_Click(object sender, EventArgs e)
        {
            string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
            SqlConnection cs = new SqlConnection(con);
            try
            {
                //SqlConnection cs = new SqlConnection(con);
                string TableName = ConfigurationManager.AppSettings["TableName"];
                SqlCommand cmd = new SqlCommand("DELETE FROM " + TableName + " WHERE ID=@cid", cs);
                cs.Open();
                cmd.Parameters.AddWithValue("@cid", Int32.Parse(dataGridView1.CurrentRow.Cells["ID"].Value.ToString()));
                cmd.ExecuteNonQuery();
                string table_name = ConfigurationManager.AppSettings["TableName"];
                string sub_table_name = ConfigurationManager.AppSettings["TableName_sub"];
                ds.Clear();
                da_class.Fill(ds, table_name);
                da_sub_class.Fill(ds, sub_table_name);
                MessageBox.Show("Deleted succesfully!");
                cs.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            finally
            {
                cs.Close();
            }
        }

        private void Update_Button_Click(object sender, EventArgs e)
        {
            string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
            try
            {
                SqlConnection cs = new SqlConnection(con);
                string TableName = ConfigurationManager.AppSettings["TableName"];
                List<string> ColumnNamesList = new List<string>(ConfigurationManager.AppSettings["ColumnNames"].Split(','));

                string UpdateQuery = ConfigurationManager.AppSettings["UpdateQuery"];
                SqlCommand cmd = new SqlCommand(UpdateQuery, cs);

                int cid = Int32.Parse(dataGridView1.CurrentRow.Cells["ID"].Value.ToString());
                cmd.Parameters.AddWithValue("@cid", cid);
                foreach (string column in ColumnNamesList)
                {
                    TextBox textBox = (TextBox)panel1.Controls[column];
                    cmd.Parameters.AddWithValue("@" + column, textBox.Text);
                }
                cs.Open();
                cmd.ExecuteNonQuery();
                string table_name = ConfigurationManager.AppSettings["TableName"];
                string sub_table_name = ConfigurationManager.AppSettings["TableName_sub"];
                ds.Clear();
                da_class.Fill(ds, table_name);
                da_sub_class.Fill(ds, sub_table_name);
                MessageBox.Show("Modified succesfully!");
                cs.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void Generate_Textboxes_Button_Click(object sender, EventArgs e)
        {
            try
            {
                List<string> ColumnNames = new List<string>(ConfigurationManager.AppSettings["ColumnNames"].Split(','));
                int pointX = 30;
                int pointY = 40;
                int numberOfColumns = Convert.ToInt32(ConfigurationManager.AppSettings["NumberOfColumns"]);
                panel1.Controls.Clear();
                foreach (string columnName in ColumnNames)
                {
                    TextBox t = new TextBox();
                    t.Text = columnName;
                    t.Name = columnName;
                    t.Location = new Point(pointX, pointY);
                    t.Visible = true;
                    t.Parent = panel1;
                    panel1.Show();
                    pointY += 30;
                }
            }
            catch (Exception)
            {
                MessageBox.Show(e.ToString());
            }
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
        private void subDataGrid_RowHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            List<string> ColumnNames = new List<string>(ConfigurationManager.AppSettings["ColumnNames_sub"].Split(','));
            scid = Convert.ToInt32(dataGridView2.CurrentRow.Cells[0].Value.ToString());
            int i = 1;
            foreach (string column in ColumnNames)
            {
                TextBox textBox = (TextBox)panel2.Controls[column];
                textBox.Text = dataGridView2.CurrentRow.Cells[i].Value.ToString();
                i++;
            }
        }

        private void insert_sub_Click(object sender, EventArgs e)
        {
            string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
            try
            {
                SqlConnection cs = new SqlConnection(con);
                string sub_table_name = ConfigurationManager.AppSettings["TableName_sub"];
                string ColumnNames = ConfigurationManager.AppSettings["ColumnNames_sub"];

                string ColumnNamesInsertParameters = ConfigurationManager.AppSettings["ColumnNamesInsertParameters_sub"];
                List<string> ColumnNamesList = new List<string>(ConfigurationManager.AppSettings["ColumnNames_sub"].Split(','));
                SqlCommand cmd = new SqlCommand("INSERT INTO " + sub_table_name + "(" + ColumnNames + ") Values (" + ColumnNamesInsertParameters + ")", cs);
                foreach (string column in ColumnNamesList)
                {
                    TextBox textBox = (TextBox)panel2.Controls[column];
                    cmd.Parameters.AddWithValue("@" + column, textBox.Text);
                }
                string table_name = ConfigurationManager.AppSettings["TableName"];
                cs.Open();
                cmd.ExecuteNonQuery();
                ds.Clear();
                da_class.Fill(ds, table_name);
                da_sub_class.Fill(ds, sub_table_name);
                MessageBox.Show("Added succesfully!");
                cs.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void delete_sub_Click(object sender, EventArgs e)
        {
            string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
            SqlConnection cs = new SqlConnection(con);
            try
            {
                //SqlConnection cs = new SqlConnection(con);
                string sub_TableName = ConfigurationManager.AppSettings["TableName_sub"];
                SqlCommand cmd = new SqlCommand("DELETE FROM " + sub_TableName + " WHERE ID=@scid", cs);
                cs.Open();
                cmd.Parameters.AddWithValue("@scid", Int32.Parse(dataGridView2.CurrentRow.Cells["ID"].Value.ToString()));
                cmd.ExecuteNonQuery();
                string table_name = ConfigurationManager.AppSettings["TableName"];
                string sub_table_name = ConfigurationManager.AppSettings["TableName_sub"];
                ds.Clear();
                da_class.Fill(ds, table_name);
                da_sub_class.Fill(ds, sub_table_name);
                MessageBox.Show("Deleted succesfully!");
                cs.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            finally
            {
                cs.Close();
            }
        }

        private void update_sub_Click(object sender, EventArgs e)
        {
            string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
            try
            {
                SqlConnection cs = new SqlConnection(con);
                string sub_TableName = ConfigurationManager.AppSettings["TableName_sub"];
                List<string> sub_ColumnNamesList = new List<string>(ConfigurationManager.AppSettings["ColumnNames_sub"].Split(','));

                string sub_UpdateQuery = ConfigurationManager.AppSettings["UpdateQuery_sub"];
                SqlCommand cmd = new SqlCommand(sub_UpdateQuery, cs);

                int scid = Int32.Parse(dataGridView2.CurrentRow.Cells["ID"].Value.ToString());
                cmd.Parameters.AddWithValue("@scid", scid);
                foreach (string column in sub_ColumnNamesList)
                {
                    TextBox textBox = (TextBox)panel2.Controls[column];
                    cmd.Parameters.AddWithValue("@" + column, textBox.Text);
                }
                cs.Open();
                cmd.ExecuteNonQuery();
                string table_name = ConfigurationManager.AppSettings["TableName"];
                string sub_table_name = ConfigurationManager.AppSettings["TableName_sub"];
                ds.Clear();
                da_class.Fill(ds, table_name);
                da_sub_class.Fill(ds, sub_table_name);
                MessageBox.Show("Modified succesfully!");
                cs.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void generate_textboxes_sub_Click(object sender, EventArgs e)
        {
            try
            {
                List<string> ColumnNames = new List<string>(ConfigurationManager.AppSettings["ColumnNames_sub"].Split(','));
                int pointX = 30;
                int pointY = 40;
                int numberOfColumns = Convert.ToInt32(ConfigurationManager.AppSettings["NumberOfColumns_sub"]);
                panel2.Controls.Clear();
                foreach (string columnName in ColumnNames)
                {
                    TextBox t = new TextBox();
                    t.Text = columnName;
                    t.Name = columnName;
                    t.Location = new Point(pointX, pointY);
                    t.Visible = true;
                    t.Parent = panel2;
                    panel2.Show();
                    pointY += 30;
                }
            }
            catch (Exception)
            {
                MessageBox.Show(e.ToString());
            }
        }
    }
}

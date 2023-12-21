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
using System.Xml.Linq;

namespace DBMSLab2
{
    public class MasterDetailLinkInfo
    {
        public string ParentTableName { get; set; }
        public string ChildTableName { get; set; }
        public string ParentIDField { get; set; }
        public string ChildIDField { get; set; }

        public MasterDetailLinkInfo(string parentTableName, string childTableName, string parentIDField, string childIDField)
        {
            ParentTableName = parentTableName;
            ChildTableName = childTableName;
            ParentIDField = parentIDField;
            ChildIDField = childIDField;
        }
    }
    public class TableInfo
    {
        public string Name { get; set; }
        public string Columns { get; set; }
        public string SelectProcedure { get; set; }
        public string InsertProcedure { get; set; }
        public string UpdateProcedure { get; set; }
        public string DeleteProcedure { get; set; }
        public List<MasterDetailLinkInfo> MasterDetailLinks { get; set; }
    }
    public partial class Form1 : Form
    {
        private string connectionString = @"Data Source=(localdb)\MSSQLLocalDB;Initial Catalog=VaccinesSM;Integrated Security=True";

        private List<MasterDetailLinkInfo> masterDetailLinks;

        public Form1()
        {
            InitializeComponent();
            LoadConfiguration();
        }

        private void LoadConfiguration()
        {
            masterDetailLinks = new List<MasterDetailLinkInfo>();

            // Load configuration from file
            // In this example, we hard-code the configuration for simplicity
            masterDetailLinks.Add(new MasterDetailLinkInfo("Cabinets", "Vaccines", "ID", "Cabinets_ID"));
            masterDetailLinks.Add(new MasterDetailLinkInfo("Vaccine_Producers", "Vaccines", "ID", "Vaccine_Producers_ID"));
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            foreach (MasterDetailLinkInfo link in masterDetailLinks)
            {
                // Create master-detail relationship for each link
                DataGridView masterGrid = new DataGridView();
                DataGridView detailGrid = new DataGridView();

                // Set the data source for the master grid
                string selectMasterQuery = $"SELECT * FROM {link.ParentTableName}";
                SqlDataAdapter masterDataAdapter = new SqlDataAdapter(selectMasterQuery, connectionString);
                DataSet masterDataSet = new DataSet();
                masterDataAdapter.Fill(masterDataSet, link.ParentTableName);
                masterGrid.DataSource = masterDataSet.Tables[link.ParentTableName];

                // Set the data source for the detail grid
                string selectDetailQuery = $"SELECT * FROM {link.ChildTableName} WHERE {link.ChildIDField}=@ID";
                SqlDataAdapter detailDataAdapter = new SqlDataAdapter(selectDetailQuery, connectionString);
                detailDataAdapter.SelectCommand.Parameters.AddWithValue("@ID", -1); // Set default value
                DataSet detailDataSet = new DataSet();
                detailDataAdapter.Fill(detailDataSet, link.ChildTableName);
                detailGrid.DataSource = detailDataSet.Tables[link.ChildTableName];

                // Add the detail grid to a new tab page in the master grid's tab control
                TabPage tabPage = new TabPage(link.ChildTableName);
                tabPage.Controls.Add(detailGrid);
                masterGrid.TabPages.Add(tabPage);

                // Create a new event handler for selecting a row in the master grid
                masterGrid.SelectionChanged += (s, args) =>
                {
                    // Update the parameter value for the detail data adapter
                    DataGridViewRow selectedRow = (s as DataGridView).CurrentRow;
                    int selectedID = Convert.ToInt32(selectedRow.Cells[link.ParentIDField].Value);
                    detailDataAdapter.SelectCommand.Parameters["@ID"].Value = selectedID;

                    // Clear the detail grid's data source and refill it with the new data
                    detailDataSet.Tables[link.ChildTableName].Clear();
                    detailDataAdapter.Fill(detailDataSet, link.ChildTableName);
                };
                masterGrid = new DataGridView();
                masterGrid.Dock = DockStyle.Fill;
                masterGrid.ReadOnly = true;
                masterGrid.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
                this.Controls.Add(masterGrid);

                // Add the detail grid to the form
                detailGrid = new DataGridView();
                detailGrid.Dock = DockStyle.Bottom;
                detailGrid.ReadOnly = true;
                detailGrid.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
                this.Controls.Add(detailGrid);

                // Create the master-detail link
                MasterDetailLinkInfo linkInfo = new MasterDetailLinkInfo();
                linkInfo.MasterColumn = "ID";
                linkInfo.DetailTable = "Vaccines";
                linkInfo.DetailColumn = "Cabinets_ID";
                linkInfo.RelatedTables.Add("Vaccine_Producers", "ID", "Vaccine_Producers_ID");
                linkInfo.RelatedTables.Add("Taken_Vaccines", "Vaccines_ID", "ID");

                // Set the data source for the master grid
                masterGrid.DataSource = GetDataSource(linkInfo.MasterTable);

                // Set the data source for the detail grid
                detailGrid.DataSource = GetDataSource(linkInfo.DetailTable);

                // Set up the data bindings for the master-detail link
                BindMasterDetailLink(linkInfo);

                // Set the captions for the master and detail grids
                SetGridCaptions(linkInfo.MasterTable, masterGrid);
                SetGridCaptions(linkInfo.DetailTable, detailGrid);
            }
        }
    }
    public class MasterDetailForm : Form
    {
        private readonly MasterDetailLinkInfo linkInfo;
        private readonly DataSet dataSet;

        public MasterDetailForm(MasterDetailLinkInfo linkInfo, DataSet dataSet)
        {
            this.linkInfo = linkInfo;
            this.dataSet = dataSet;

            InitializeComponent();
        }

        private void MasterDetailForm_Load(object sender, EventArgs e)
        {
            // Set the form caption
            this.Text = linkInfo.FormCaption;

            // Set up the master DataGridView
            var masterBindingSource = new BindingSource();
            masterBindingSource.DataSource = dataSet;
            masterBindingSource.DataMember = linkInfo.MasterTableName;

            dataGridViewMaster.DataSource = masterBindingSource;

            // Set up the detail DataGridView
            var detailBindingSource = new BindingSource();
            detailBindingSource.DataSource = masterBindingSource;
            detailBindingSource.DataMember = linkInfo.RelationName;

            dataGridViewDetail.DataSource = detailBindingSource;
        }
    }
}

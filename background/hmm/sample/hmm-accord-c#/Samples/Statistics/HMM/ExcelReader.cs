using System;
using System.Collections.Generic;
using System.Text;

using System.Data;
using System.Data.OleDb;


namespace Components
{
    public class ExcelReader
    {

        private string path;
        private string strConnection;


        public ExcelReader(string path, bool hasHeaders, bool hasMixedData)
        {
            this.path = path;
            OleDbConnectionStringBuilder strBuilder = new OleDbConnectionStringBuilder();
            strBuilder.Provider = "Microsoft.Jet.OLEDB.4.0";
            strBuilder.DataSource = path;
            strBuilder.Add("Extended Properties", "Excel 8.0;"+
                "HDR=" + (hasHeaders ? "Yes" : "No") + ';' +
                "Imex=" + (hasMixedData ? "2" : "0") + ';' +
              ""); 

            
            strConnection = strBuilder.ToString();
        }

        public string[] GetWorksheetList()
        {
            string[] worksheets;

            try
            {
                OleDbConnection connection = new OleDbConnection(strConnection);
                connection.Open();
                DataTable tableWorksheets = connection.GetSchema("Tables");
                connection.Close();

                worksheets = new string[tableWorksheets.Rows.Count];

                for (int i = 0; i < worksheets.Length; i++)
                {
                    worksheets[i] = (string)tableWorksheets.Rows[i]["TABLE_NAME"];
                    worksheets[i] = worksheets[i].Remove(worksheets[i].Length - 1).Trim('"', '\'');
                    // removes the trailing $ and other characters appended in the table name
                    while (worksheets[i].EndsWith("$"))
                        worksheets[i] = worksheets[i].Remove(worksheets[i].Length - 1).Trim('"', '\'');
                }
            }
            catch 
            {
                /* 
                    for (int i = 0; i < ex.Errors.Count; i++)
                    {
                        MessageBox.Show("Index #" + i + "\n" +
                        "Message: " + myException.Errors[i].Message + "\n" +
                        "Native: " +
                            myException.Errors[i].NativeError.ToString() + "\n" +
                        "Source: " + myException.Errors[i].Source + "\n" +
                        "SQL: " + myException.Errors[i].SQLState + "\n");
                    }
                 */
                throw;
            }

            return worksheets;
        }

        public string[] GetColumnsList(string worksheet)
        {
            string[] columns;

            try
            {
                OleDbConnection connection = new OleDbConnection(strConnection);
                connection.Open();
                DataTable tableColumns = connection.GetSchema("Columns", new string[] {null, null, worksheet + '$', null});
                connection.Close();

                columns = new string[tableColumns.Rows.Count];

                for (int i = 0; i < columns.Length; i++)
                {
                    columns[i] = (string)tableColumns.Rows[i]["COLUMN_NAME"];
                }
            }
            catch
            {
                throw;
            }

            return columns;
        }

        public DataTable GetWorksheet(string worksheet)
        {
            DataTable ws;

            OleDbConnection connection = new OleDbConnection(strConnection);
            OleDbDataAdapter adaptor = new OleDbDataAdapter(String.Format("SELECT * FROM [{0}$]", worksheet), connection);
            ws = new DataTable(worksheet);
            adaptor.FillSchema(ws, SchemaType.Source);
            adaptor.Fill(ws);

            adaptor.Dispose();
            connection.Close();

            return ws;
        }

        public DataSet GetWorkplace()
        {
            DataSet workplace;

            OleDbConnection connection = new OleDbConnection(strConnection);
            OleDbDataAdapter adaptor = new OleDbDataAdapter("SELECT * FROM *", connection);
            workplace = new DataSet();
            adaptor.FillSchema(workplace, SchemaType.Source);
            adaptor.Fill(workplace);

            adaptor.Dispose();
            connection.Close();

            return workplace;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Data;
using System.Collections.ObjectModel;
using System.Windows.Markup;
using System.IO;
using Microsoft.Win32;

namespace ModelManager {

    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window {

        public DataTable mainTable = new DataTable();
        public DataTable BufferTable = new DataTable();
        private bool isManualEditCommit, isRowCommited;


        public MainWindow()
        {
            InitializeComponent();
        }


        ///<summary>
        ///データテーブルに新規に追加
        ///</summary>
        private void Add_Row(object sender, RoutedEventArgs e)
        {

        }

        /// <summary>
        /// 新規Windowを表示する
        /// </summary>
        private void Add_Columns(object sender, RoutedEventArgs e)
        {
            Window window = new ChangeMaxAnimeNum();
            window.Owner = this;
            window.Show();
        }

        /// <summary>
        /// テーブルの更新
        /// </summary>
        public void ChangeTable(int columns,int rows)
        {
            DataTable chengeTable = new DataTable();

            var CheckBox = new DataColumn("ボーンか", typeof(bool));
            CheckBox.AllowDBNull = false;
            CheckBox.DefaultValue = false;
            chengeTable.Columns.Add(CheckBox);
            chengeTable.Columns.Add("ファイルネーム");
            chengeTable.Columns.Add("キーネーム");
            for (int i = 1;i<columns+1;i++) {
                chengeTable.Columns.Add("第" + i + "アニメーションの名前");
                chengeTable.Columns.Add("第" + i + "アニメーション開始時間");
                chengeTable.Columns.Add("第" + i + "アニメーション持続時間");
            }
            for (int j = 0;j<rows;j++)
            {
                chengeTable.Rows.Add();
            }
            ModelTable.AutoGenerateColumns = true;
            ModelTable.CanUserAddRows = false;

            ModelTable.DataContext = chengeTable;
            ModelTable.Items.Refresh();
        }

        /// <summary>
        /// CSV書き出し
        /// </summary>
        private void FileSave(object sender, RoutedEventArgs e)
        {

            //ダイアログ表示
            SaveFileDialog dialog = new SaveFileDialog();
            //デフォルトネーム
            dialog.FileName = "model.csv";
            //デフォルトディレクトリ
            dialog.InitialDirectory = @"c:\";
            //フィルタ
            dialog.Filter = "CSVファイル|*.csv";
            //種類
            dialog.FilterIndex = 0;
            if (dialog.ShowDialog() == true)
            {
                mainTable = ((DataView)ModelTable.ItemsSource).ToTable().Copy();

                //CSVファイルに書き込むときに使うEncoding
                System.Text.Encoding enc =
                    System.Text.Encoding.GetEncoding("Shift_JIS");

                //書き込むファイルを開く
                System.IO.StreamWriter sr =
                    new System.IO.StreamWriter(dialog.FileName,false,enc);

                int colCount = ModelTable.Columns.Count;

                for (int i = 0;i < mainTable.Rows.Count;i++)
                {
                    for (int j = 0;j < mainTable.Columns.Count;j++)
                    {
                        switch (mainTable.Rows[i][j].ToString())
                        {
                            case null:
                                sr.Write(",");
                                break;
                            default:
                                sr.Write(mainTable.Rows[i][j].ToString());
                                sr.Write(",");
                                break;
                        }

                        if (j == (colCount-1))
                        {
                            sr.Write("END");
                            sr.Write("\n");
                        }

                    }
                }
                sr.Close();
            }
        }
        /// <summary>
        /// テーブルの入力状態を見て確定するイベント
        /// </summary>
        private void ModelTable_SourceUpdated(object sender, DataGridCellEditEndingEventArgs e)
        {

            if (!isManualEditCommit)
            {
                isManualEditCommit = true;
                DataGrid grid = (DataGrid)sender;
                grid.CommitEdit(DataGridEditingUnit.Row, true);
                isRowCommited = true;
                isManualEditCommit = false;
            }
        }
    }
}

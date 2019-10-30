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
using System.Windows.Shapes;

namespace ModelManager {
    /// <summary>
    /// ChangeMaxAnimeNum.xaml の相互作用ロジック
    /// </summary>
    public partial class ChangeMaxAnimeNum : Window {
        public ChangeMaxAnimeNum()
        {
            InitializeComponent();
        }

        private void SetButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow =(MainWindow)Owner;
            int colmus;
            int rows;
            if (!int.TryParse(MaxAnimNum.Text,out colmus) || (!int.TryParse(MaxModelNum.Text, out rows)))
            {
                MessageBox.Show(" 数字以外が入力されています！", "警告！", MessageBoxButton.OK, MessageBoxImage.Warning);
                MaxAnimNum.Text = "0";
                MaxModelNum.Text = "0";
            }
            else
            {
                mainWindow.ChangeTable(colmus,rows);
            }
        }
    }
}

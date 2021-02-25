using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System.IO;

namespace ScriptEditor
{
	//-------------------------------------------------------------
	//	イメージ選択フォーム
	//-------------------------------------------------------------
	public partial class FormImage : Form
	{
		//イメージリスト参照
		public BindingList<ImageData> L_ImageData { get; set; }

		//選択中イメージのインデックス
		public int GetImageIndex () { return Lb_Image.SelectedIndex; }

		//グループ編集用
		public ScriptParam < int > ScriptSetter { get; set; } = null;

		//コンストラクタ
		public FormImage ( BindingList<ImageData> listImageData )
		{
			//フォーム開始位置
			this.StartPosition = FormStartPosition.Manual;
			this.Location = Cursor.Position;

			InitializeComponent ();

			//内部参照
			L_ImageData = listImageData;

			//リストボックスに反映
			Lb_Image.DisplayMember = "Name";
			Lb_Image.ValueMember = "Image";
			Lb_Image.DataSource = listImageData;
		}

		//リストボックス変更時
		private void listBox1_SelectedIndexChanged ( object sender, EventArgs e )
		{
			//選択されていないとき何もしない
			if ( null == Lb_Image.SelectedItem ) { return; }

			pbArchiveImage.Image = ( ( ImageData ) Lb_Image.SelectedItem ).Img;
		}

		//キャンセル
		private void btn_Cancel_Click ( object sender, EventArgs e )
		{
			this.Close ();			//何もせずに終了
		}

		//OKはShowDialog()で開いた後、DialogResultから指定する

		private void 読込ToolStripMenuItem_Click ( object sender, EventArgs e )
		{
			//複数のファイルを選択できるようにする
			openFileDialog1.Multiselect = true;
			openFileDialog1.FileName = "";

			if ( openFileDialog1.ShowDialog () == DialogResult.OK )
			{
				foreach ( string filename in openFileDialog1.FileNames )
				{
					ImageData imageData = null;	//参照
					try
					{
						//画像からImageData型を作成
						imageData = new ImageData ( Path.GetFileName ( filename ), Image.FromFile ( filename ) );
						L_ImageData.Add ( imageData );			//内部データに保存
						pbArchiveImage.Image = imageData.Img;			//プレビューにImageを表示
						Lb_Image.SelectedIndex = Lb_Image.Items.Count - 1;		//末尾を選択
					}
					catch ( System.OutOfMemoryException ex )
					{
						//ファイル形式が有効でないとき
						MessageBox.Show ( "ファイル形式が無効です。\n" + ex.Message );
						return;
					}
				}
			}
		}

		private void 全削除ToolStripMenuItem_Click ( object sender, EventArgs e )
		{
			//個数が０のときは何もしない
			if ( Lb_Image.Items.Count == 0 ) { return; }

			//未選択時は何もしない
			if ( Lb_Image.SelectedItem == null ) { return; }

			//全イメージを削除
			L_ImageData.Clear ();

			//表示をクリア
			pbArchiveImage.Image = null;
		}

	}
}

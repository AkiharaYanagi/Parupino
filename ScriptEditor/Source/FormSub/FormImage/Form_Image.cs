﻿using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System.IO;

using ScriptEditorUtility;


namespace ScriptEditor
{
	//-------------------------------------------------------------
	//	イメージ選択フォーム
	//-------------------------------------------------------------
	//このフォームは１タスク１フォームなのでシングルトンで実装する
	//静的で単一な実体化	//static
	//継承禁止	//sealed
	//プライベートコンストラクタ
	//---------------------------------------------------------------------
	public sealed partial class FormImage : Form
	{
		//---------------------------------------------------------------------
		//シングルトン実体
		public static FormImage Inst { get; } = new FormImage ();

		//プライベートコンストラクタ
		private FormImage ()
		{
			//フォーム開始位置
			this.StartPosition = FormStartPosition.Manual;
			this.Location = Cursor.Position;
			this.ShowInTaskbar = false;	//タスクバーに非表示

			InitializeComponent ();

			Lb_Image.DisplayMember = "Name";
			Lb_Image.ValueMember = "Image";
		}

		//閉じたときに破棄しない
		protected override void OnFormClosing ( FormClosingEventArgs e )
		{
			e.Cancel = true;
			this.Hide ();
		}

		//表示反転
		public void VisFlip ()
		{
			this.Visible = ! this.Visible;
		}
		//---------------------------------------------------------------------

		//編集参照
		public EditCompend EditCompend { get; set; } = null;

		//[out] グループ編集用
		public ScriptParam < int > ScriptSetter { get; set; } = null;

		//親フォーム参照
		public FormMain FormMain { get; set; } = null;

		//[in] イメージリスト参照
//		private BindingList<ImageData> L_ImageData { get; set; }
		private BindingDictionary < ImageData > BD_ImageData { get; set; }

		//---------------------------------------------------------------------
		//選択中イメージのインデックス
		public int GetImageIndex () { return Lb_Image.SelectedIndex; }
		//選択中イメージの名前
		public string GetImageName () { return ( (ImageData)Lb_Image.SelectedItem ).Name; }

		//対象を設定
#if false
		public void SetTarget ( BindingList<ImageData> bl_ImgDt )
		{
			L_ImageData = bl_ImgDt;

			//リストボックスに反映
			Lb_Image.DataSource = L_ImageData;
		}
#endif

		public void Set ( BindingDictionary < ImageData > bd_imgDt )
		{
			BD_ImageData = bd_imgDt;

			//リストボックスに反映
			Lb_Image.DataSource = BD_ImageData.GetBindingList ();
		}

		//リストボックス変更時
		private void listBox1_SelectedIndexChanged ( object sender, EventArgs e )
		{
			//選択されていないとき何もしない
			if ( null == Lb_Image.SelectedItem ) { return; }

			pbArchiveImage.Image = ( ( ImageData ) Lb_Image.SelectedItem ).Img;
		}

		//キャンセル
		private void Btn_Cancel_Click ( object sender, EventArgs e )
		{
			this.Close ();			//何もせずに終了
		}

		//OK
		private void Btn_ArchiveOK_Click ( object sender, EventArgs e )
		{
			//選択中スクリプトにイメージの設定
			Script scp = EditCompend.SelectedScript;
			scp.ImgIndex = GetImageIndex ();
			scp.ImgName = GetImageName ();
			
			//グループにも変更を反映
			EditCompend.EditScript.GroupSetterImageIndex ( scp.ImgIndex );

			this.Hide ();
		}

		private void 読込ToolStripMenuItem_Click ( object sender, EventArgs e )
		{
			//複数のファイルを選択できるようにする
			openFileDialog1.Multiselect = true;
			openFileDialog1.FileName = "";

			if ( openFileDialog1.ShowDialog () == DialogResult.OK )
			{
				LoadFiles ( openFileDialog1.FileNames );
			}
		}

		private void 全削除ToolStripMenuItem_Click ( object sender, EventArgs e )
		{
			//個数が０のときは何もしない
			if ( Lb_Image.Items.Count == 0 ) { return; }

			//未選択時は何もしない
			if ( Lb_Image.SelectedItem == null ) { return; }

			//全イメージを削除
			//L_ImageData.Clear ();
			BD_ImageData.Clear ();

			//表示をクリア
			pbArchiveImage.Image = null;
		}

		private void FormImage_VisibleChanged ( object sender, EventArgs e )
		{
			//フォーム位置を親フォームの右端にする
			int x = FormMain.Location.X + FormMain.Width;
			int y = FormMain.Location.Y;
			this.Location = new Point ( x, y );

		}

		private void フォルダ読込ToolStripMenuItem_Click ( object sender, EventArgs e )
		{
			OpenFolder_CodePack opf = new OpenFolder_CodePack ();
			string crDir = Directory.GetCurrentDirectory ();
			string upDir = crDir.Substring ( 0, crDir.LastIndexOf ( @"\" ) + 1 );
			opf.SetInitDir ( crDir );
			opf.SetDefaultFilename ( "out" );

			if ( opf.OpenFolder () )
			{
				string[] files = Directory.GetFiles ( opf.GetPath () );
				LoadFiles ( files );
			}
#if false

			folderBrowserDialog1.SelectedPath = Directory.GetCurrentDirectory ();
			if ( folderBrowserDialog1.ShowDialog ( this ) == DialogResult.OK )
			{
				string[] files = Directory.GetFiles ( folderBrowserDialog1.SelectedPath );
				LoadFiles ( files );
			}
#endif
		}

		private void LoadFiles ( string[] files )
		{
			foreach ( string filename in files )
			{
				ImageData imageData = null;	//参照
				try
				{
					//画像からImageData型を作成
					imageData = new ImageData ( Path.GetFileName ( filename ), Image.FromFile ( filename ) );

					//L_ImageData.Add ( imageData );			//内部データに保存
					BD_ImageData.Add ( imageData );
					
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
}

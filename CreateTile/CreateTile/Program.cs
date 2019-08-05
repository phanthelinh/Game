using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace CreateTile
{
    class Program
    {
        public Dictionary<int, Bitmap> lstTileSet = new Dictionary<int, Bitmap>();
        public static string enviroment = System.Environment.CurrentDirectory;
        public string projectDirectory = Directory.GetParent(enviroment).Parent.FullName;
        public static string CSVNAME = "scene4.csv";
        public static string InputFilName = "scene4_1.png";
        public static string OutputFileName = "scene4.png";
        public bool IsEqual(Bitmap bmp1, Bitmap bmp2)
        {
            if (object.Equals(bmp1, bmp2))
                return true;

            int bytes = bmp1.Width * bmp1.Height * (Image.GetPixelFormatSize(bmp1.PixelFormat) / 8) - 1;

            bool result = true;
            var b1bytes = new byte[bytes];
            var b2bytes = new byte[bytes];

            var bitmapData1 = bmp1.LockBits(new Rectangle(0, 0, bmp1.Width, bmp1.Height), ImageLockMode.ReadOnly, bmp1.PixelFormat);
            var bitmapData2 = bmp2.LockBits(new Rectangle(0, 0, bmp2.Width, bmp2.Height), ImageLockMode.ReadOnly, bmp2.PixelFormat);

            Marshal.Copy(bitmapData1.Scan0, b1bytes, 0, bytes);
            Marshal.Copy(bitmapData2.Scan0, b2bytes, 0, bytes);

            for (int n = 0; n < bytes; ++n)
            {
                if (b1bytes[n] != b2bytes[n])
                {
                    result = false;
                    break;
                }
            }

            bmp1.UnlockBits(bitmapData1);
            bmp2.UnlockBits(bitmapData2);

            return result;
        }
        public int AlreadyIncluded(Dictionary<int, Bitmap> source, Bitmap bitmap)
        {
            if (source.Count <1)
            {
                return -1;
            }
            foreach (var b in source)
            {
                if (IsEqual(b.Value, bitmap))
                {
                    return b.Key;
                }
            }
            return -1;
        }
        public Bitmap CropTile(Bitmap source, Rectangle sourceRect)
        {
            // An empty bitmap which will hold the cropped image
            Bitmap bmp = new Bitmap(sourceRect.Width, sourceRect.Height);
            Rectangle destRect = new Rectangle(0, 0, 16, 16);

            using (Graphics g = Graphics.FromImage(bmp))
            {
                // Draw the given area (section) of the source image
                // at location 0,0 on the empty bitmap (bmp)
                g.DrawImage(source, destRect, sourceRect, GraphicsUnit.Pixel);
            }

            return bmp;
        }
        public void CreateTileFromPicture(string filePath)
        {
            filePath = Path.Combine(projectDirectory, filePath);
            if (!File.Exists(filePath))
            {
                Console.WriteLine("File Path Invalid");
                return;
            }

            if (!filePath.EndsWith(".png") && !filePath.EndsWith(".PNG"))
            {
                Console.WriteLine("File is not an image");
                return;
            }

            Bitmap img = new Bitmap(filePath);
            int numTilesWidth = img.Width / 16;
            int numTilesHeight = img.Height / 16;
            List<Bitmap> lstTiles = new List<Bitmap>();
            //cut image into species
            for (int row = 0; row < numTilesHeight; row++)
            {
                for (int col = 0; col < numTilesWidth; col++)
                {
                    Rectangle sourceRect = new Rectangle(16 * col, 16 * row, 16, 16);
                    lstTiles.Add(CropTile(img, sourceRect));
                }
            }
            if (lstTiles.Count <= 0)
            {
                Console.WriteLine("Could no cut into tiles");
                return;
            }
            //initialize
            lstTileSet.Clear();
            List<int> lstId = new List<int>();
            //Minimize
            int index = 0;
            int res = -1;
            foreach (var tile in lstTiles)
            {
                res = AlreadyIncluded(lstTileSet, tile);
                if (res == -1)
                {
                    lstTileSet.Add(index, tile);
                    lstId.Add(index);
                    index++;
                }
                else
                    lstId.Add(res);
            }
            //end write to file
            StreamWriter streamWriter = new StreamWriter(Path.Combine(projectDirectory, "Resources/"+CSVNAME));
            streamWriter.Write(String.Join("\n", lstId));
            streamWriter.Close();
            //draw to image
            //calculate szie of image
            Bitmap finalImg = new Bitmap(16 * lstTileSet.Count, 16);
            //Bitmap finalImg = new Bitmap(numTilesWidth * 16, numTilesHeight * 16);
            using (Graphics g = Graphics.FromImage(finalImg))
            {
                g.Clear(Color.Black);
                for(int i =0; i<lstTileSet.Count;i++)
                {
                    g.DrawImage(lstTileSet[i], new Rectangle(i * 16, 0, 16, 16), new Rectangle(0, 0, 16, 16), GraphicsUnit.Pixel);
                }
                //for (int row = 0; row < numTilesHeight; row++)
                //{
                //    for (int col = 0; col < numTilesWidth; col++)
                //    {
                //        Image t = lstTiles.ElementAt(col + row * numTilesWidth);
                //        g.DrawImage(t, new Rectangle(col * 16, row * 16, t.Width, t.Height));

                //    }
                //}
            }
            finalImg.Save(Path.Combine(projectDirectory, "Resources/"+OutputFileName));
        }

        static void Main(string[] args)
        {
            Program pro = new Program();
            string filename = @"Resources/"+InputFilName;

            pro.CreateTileFromPicture(filename);
        }
    }
}
